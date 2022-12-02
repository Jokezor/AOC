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
    ["A", "Y"] -> 8
    ["B", "Z"] -> 9
    ["C", "X"] -> 7
    ["A", "X"] -> 4
    ["B", "Y"] -> 5
    ["C", "Z"] -> 6
    [_, "X"] -> 1
    [_, "Y"] -> 2
    [_, "Z"] -> 3
    _ -> 0

