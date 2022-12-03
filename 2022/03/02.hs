import Data.List
import Data.Char
import Data.Set (Set, fromList, intersection, elemAt)


main :: IO ()
main = do
  s <- readFile "input.txt"
  let splitLines = lines s

  let groupLines = groupThree splitLines

  -- Make a set from the groups
  let duplicate = (map getIntersection groupLines)

  print duplicate

  -- Convert to ascii number order
  print (sum (map convertToPriority duplicate))

groupThree :: [a] -> [[a]]
groupThree [] = []
groupThree ls = (take 3 ls):groupThree (drop 3 ls)

convertToPriority :: Char -> Int
convertToPriority item = 
  if isUpper item
    then ord item - (ord 'A' - 27)
  else
    ord item - (ord 'a' - 1)


getIntersection :: [String] -> Char
getIntersection [first, second, third] =
  elemAt 0 (intersection (intersection (fromList first) (fromList second)) (fromList third))

assertEqual :: (String, String) -> Bool
assertEqual (first, second) = length(first) == length(second)

