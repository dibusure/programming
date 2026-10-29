import os
import tempfile
import subprocess
from pathlib import Path

from telegram import Update
from telegram.ext import (
    ApplicationBuilder,
    MessageHandler,
    CommandHandler,
    ContextTypes,
    filters,
)

BOT_TOKEN = os.environ["BOT_TOKEN"]
CONVERT_TIMEOUT = 99999

SCRIPT_PATH = Path(__file__).resolve().parent / "convert.sh"
SCRIPTT_PATH = Path(__file__).resolve().parent / "convert_stat.sh"


async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text(
        "Send me a *video sticker (webm)* or a *static sticker (webp)* and I will convert it to GIF.",
        parse_mode="Markdown",
    )


async def handle_sticker(update: Update, context: ContextTypes.DEFAULT_TYPE):
    sticker = update.message.sticker

    # Reject Lottie stickers explicitly
    if sticker.is_animated and not sticker.is_video:
        await update.message.reply_text("Animated .tgs stickers are not supported.")
        return

    await update.message.reply_text("Processing…")

    with tempfile.TemporaryDirectory() as tmpdir:
        tmpdir = Path(tmpdir)

        # Decide paths based on sticker type
        if sticker.is_video:
            input_file = tmpdir / "sticker.webm"
            output_file = tmpdir / "sticker.gif"

            file = await context.bot.get_file(sticker.file_id)
            await file.download_to_drive(input_file)

            try:
                subprocess.run(
                    [str(SCRIPT_PATH), input_file.name],
                    cwd=tmpdir,
                    check=True,
                    timeout=CONVERT_TIMEOUT,
                )
            except subprocess.SubprocessError as e:
                await update.message.reply_text(f"Video conversion failed: {e}")
                return

        else:
            # Static sticker (webp)
            input_file = tmpdir / "sticker.webp"
            output_file = tmpdir / "sticker.gif"

            file = await context.bot.get_file(sticker.file_id)
            await file.download_to_drive(input_file)

            try:
                subprocess.run(
                    [str(SCRIPTT_PATH), input_file],
                    cwd=tmpdir,
                    check=True,
                    timeout=CONVERT_TIMEOUT,
                )
            except subprocess.SubprocessError as e:
                await update.message.reply_text(f"Image conversion failed: {e}")
                return

        if not output_file.exists():
            await update.message.reply_text("GIF was not produced.")
            return

        with open(output_file, "rb") as gif:
            await update.message.reply_animation(animation=gif)


def main():
    app = ApplicationBuilder().token(BOT_TOKEN).build()

    app.add_handler(CommandHandler("start", start))
    app.add_handler(MessageHandler(filters.Sticker.ALL, handle_sticker))

    app.run_polling()


if __name__ == "__main__":
    main()

