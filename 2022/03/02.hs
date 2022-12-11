import Data.List as L
import Data.Char
import Data.Set as S


main :: IO ()
main = do
  s <- readFile "input.txt"
  let splitLines = lines s

  let groupLines = groupThree splitLines

  -- Make a set from the groups
  let duplicate = (L.map getIntersection groupLines)

  print duplicate

  -- Convert to ascii number order
  print (sum (L.map convertToPriority duplicate))

groupThree :: [a] -> [[a]]
groupThree [] = []
groupThree ls = (L.take 3 ls):groupThree (L.drop 3 ls)

convertToPriority :: Char -> Int
convertToPriority item
  | isUpper item = ord item - (ord 'A' - 27)
  | otherwise = ord item - (ord 'a' - 1)

getIntersection :: [String] -> Char
getIntersection [first, second, third] =
  S.findMin (c1 `S.intersection` (c2 `S.intersection` c3))
  where c1 = S.fromList first
        c2 = S.fromList second
        c3 = S.fromList third

