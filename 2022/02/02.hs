import Data.List.Split

main :: IO ()
main = do
  s <- readFile "input.txt"
  let sLines = lines s
  let l = map (splitOn " ") sLines
  let myTotScore = myScore l
  print l
  print myTotScore

myScore :: [[String]] -> Int
myScore strategy =  (foldl calcScore 0 strategy)

calcScore :: Int -> [String] -> Int
calcScore totScore [opponent, me] = 
  if me == "X" then 
      (if opponent == "A" then 
          totScore + 3
      else if opponent == "C" then 
          totScore + 2
      else if opponent == "B" then
          totScore + 1
      else
          totScore
      )
  else if me == "Y" then
      (if opponent == "A" then
          totScore + 1 + 3
       else if opponent == "B" then
          totScore + 2 + 3
       else if opponent == "C" then
           totScore + 3 + 3
       else
           totScore
      )
  else if me == "Z" then
      (if opponent == "A" then
          totScore + 2 + 6
       else if opponent == "B" then
          totScore + 3 + 6
       else if opponent == "C" then
          totScore + 1 + 6
       else 
          totScore
      )
  else totScore
  
