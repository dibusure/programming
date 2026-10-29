-- Демонстрационный файл для проверки подсветки Haskell.
-- Его можно удалить: это не часть твоих решений.

module Main where

-- Бесконечный список, который вычисляется по мере необходимости.
fibonacci :: [Integer]
fibonacci = 0 : 1 : zipWith (+) fibonacci (tail fibonacci)

sumOfSquares :: Integer -> Integer
sumOfSquares n = sum [x * x | x <- [1 .. n]]

main :: IO ()
main = do
  putStrLn "Hello, Haskell!"
  putStrLn "Первые 12 чисел Фибоначчи:"
  print (take 12 fibonacci)
  putStrLn "Сумма квадратов от 1 до 10:"
  print (sumOfSquares 10)
