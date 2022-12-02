import Data.List.Split

main :: IO ()
main = do
  s <- readFile "input.txt"
  let sLines = lines s
  let strategy = map (splitOn " ") sLines
  let myTotScore = sum (map calcOutcomeScore strategy)
  print myTotScore

calcOutcomeScore :: [String] -> Int
calcOutcomeScore move =
  case move of
    ["A", "X"] -> 3
    ["B", "X"] -> 1
    ["C", "X"] -> 2

    ["A", "Y"] -> 4
    ["B", "Y"] -> 5
    ["C", "Y"] -> 6

    ["A", "Z"] -> 8
    ["B", "Z"] -> 9
    ["C", "Z"] -> 7
    _ -> 0

