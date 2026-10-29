import os
import tempfile
import subprocess
from pathlib import Path
import asyncio

from telegram import Update
from telegram.ext import ApplicationBuilder, CommandHandler, MessageHandler, ContextTypes, filters

import discord

# ---------------- Configuration ----------------
TELEGRAM_BOT_TOKEN = os.environ["BOT_TOKEN"]       # Telegram bot token
DISCORD_BOT_TOKEN = os.environ["DISCORD_TOKEN"]    # Discord bot token
DISCORD_USER_ID = 123456789012345678              # Replace with debusure's Discord user ID
CONVERT_SCRIPT = Path(__file__).parent / "convert.sh"
CONVERT_TIMEOUT = 60  # seconds
# ------------------------------------------------

# Discord client
discord_intents = discord.Intents.default()
discord_intents.dm_messages = True
discord_client = discord.Client(intents=discord_intents)

# Telegram bot app
telegram_app = ApplicationBuilder().token(TELEGRAM_BOT_TOKEN).build()


# ---------- Telegram Bot Handlers ----------
async def start(update: Update, context: ContextTypes.DEFAULT_TYPE):
    await update.message.reply_text(
        "Send me a *video sticker* (WebM). I will convert it to GIF and send it to debusure.",
        parse_mode="Markdown"
    )


async def handle_sticker(update: Update, context: ContextTypes.DEFAULT_TYPE):
    sticker = update.message.sticker

    if not sticker.is_video:
        await update.message.reply_text("Only video stickers (WebM) are supported.")
        return

    processing_msg = await update.message.reply_text("Processing sticker…")

    try:
        with tempfile.TemporaryDirectory() as tmp:
            tmp_path = Path(tmp)
            input_file = tmp_path / "sticker.webm"

            # Download sticker
            file = await context.bot.get_file(sticker.file_id)
            await file.download_to_drive(input_file)

            # Run convert.sh inside temp dir
            subprocess.run(
                [str(CONVERT_SCRIPT), input_file.name],
                cwd=tmp_path,
                check=True,
                timeout=CONVERT_TIMEOUT
            )

            # Determine GIF output
            possible_outputs = list(tmp_path.glob("*.gif"))
            if not possible_outputs:
                await processing_msg.edit_text("Conversion script did not produce a GIF.")
                return

            gif_file = possible_outputs[0]

            # Send GIF back to Telegram user
            with open(gif_file, "rb") as f:
                await update.message.reply_animation(animation=f)

            # Send GIF to Discord user
            await send_to_discord(gif_file)

            await processing_msg.delete()

    except subprocess.SubprocessError as e:
        await processing_msg.edit_text(f"Conversion failed: {e}")
    except Exception as e:
        await processing_msg.edit_text(f"Unexpected error: {e}")


# ---------- Discord Integration ----------
async def send_to_discord(gif_path: Path):
    await discord_client.wait_until_ready()
    try:
        user = await discord_client.fetch_user(DISCORD_USER_ID)
        if user:
            await user.send(file=discord.File(gif_path))
            print(f"Sent GIF to Discord: {gif_path.name}")
    except Exception as e:
        print(f"Failed to send GIF to Discord: {e}")


# ---------- Combined Startup ----------
async def start_bots():
    # Start Discord bot concurrently
    asyncio.create_task(discord_client.start(DISCORD_BOT_TOKEN))
    # Start Telegram bot polling
    await telegram_app.run_polling()


# ---------- Register Handlers ----------
telegram_app.add_handler(CommandHandler("start", start))
telegram_app.add_handler(MessageHandler(filters.Sticker.ALL, handle_sticker))

# ---------- Entry Point ----------
# Works in scripts, IDEs, or Jupyter without asyncio.run()
import asyncio

async def main():
    await start_bots()  # your coroutine that runs both bots

# Check if a loop is already running
try:
    loop = asyncio.get_running_loop()
except RuntimeError:
    loop = None

if loop and loop.is_running():
    # Already inside an event loop (e.g., Jupyter)
    asyncio.create_task(main())
else:
    # No loop — create one
    asyncio.run(main())

