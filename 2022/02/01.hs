import Data.List.Split

main :: IO ()
main = do
  s <- readFile "input.txt"
  let sLines = lines s
  let strategy = map (splitOn " ") sLines
  let myTotScore = myScore strategy
  print strategy
  print myTotScore

myScore :: [[String]] -> Int
myScore strategy = foldl calcScore 0 strategy

calcOutcomeScore :: [String] -> Int
calcOutcomeScore move =
  case move of
    ["A", "Y"] -> 6
    ["B", "Z"] -> 6
    ["C", "X"] -> 6
    ["A", "X"] -> 3
    ["B", "Y"] -> 3
    ["C", "Z"] -> 3
    _ -> 0

calcScore :: Int -> [String] -> Int
calcScore totScore [opponent, me] = 
  if me == "X" then 
      totScore + (calcOutcomeScore [opponent, me]) + 1
  else if me == "Y" then
      totScore + (calcOutcomeScore [opponent, me]) + 2
  else if me == "Z" then
      totScore + (calcOutcomeScore [opponent, me]) + 3
  else totScore
  
