"""Демонстрация подсветки Python. Файл можно удалить."""


def fibonacci(count: int) -> list[int]:
    result = []
    a, b = 0, 1
    for _ in range(count):
        result.append(a)
        a, b = b, a + b
    return result


if __name__ == "__main__":
    print("Hello, Python!")
    print(fibonacci(12))
