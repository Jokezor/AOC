import Data.List
import Data.Char
import Data.Set (Set, fromList, intersection, elemAt)


main :: IO ()
main = do
  s <- readFile "input.txt"
  let sLines = lines s
  --let splitLit = substring 0 ((length (head sLines)) / 2) (head sLines)
  print sLines
  let splitLines = map splitString sLines

  -- Check that all substrings are of same size
  print (map assertEqual splitLines)

  -- Make a set from the split string
  let duplicate = (map getIntersection splitLines)

  print duplicate

  -- Convert to ascii number order
  print (sum (map convertToPriority duplicate))

convertToPriority :: Char -> Int
convertToPriority item = 
  if isUpper item
    then ord item - (ord 'A' - 27)
  else
    ord item - (ord 'a' - 1)


getIntersection :: (String, String) -> Char
getIntersection (first, second) =
  elemAt 0 (intersection (fromList first) (fromList second))

assertEqual :: (String, String) -> Bool
assertEqual (first, second) = length(first) == length(second)


slice :: Int -> Int -> String -> String
slice off n = (take n).(drop off)

splitString :: String -> (String, String)
splitString s =
  ((slice 0 (length(s) `div` 2) (s)), (slice (length(s) `div` 2) (length(s)) (s)))



