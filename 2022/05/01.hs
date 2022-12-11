import Data.List as L
import Data.List.Split
import Data.Char

main :: IO ()
main = do
  s <- readFile "example_input.txt"
  let sLines = lines s
  print sLines
  let parsed = parseInput sLines
  print parsed
  let arrays = getCombinedArrays [[], [], []] (L.take 3 parsed)
  print arrays
  let onlyArray = map (takeOnlyArray ([[], [], []])) arrays
  print onlyArray

  -- combine arrays
  print (concat [["D"], [], ["P"]])
  let concatArray = ((getConcatArray 0) 0) [[["D"], [], ["P"]]]
  print concatArray


  --let combinedArrays = foldl combineArray [[], [], []] arrays
  --print combinedArrays

getConcatArray :: Int -> Int -> [[[String]]] -> [[String]]
getConcatArray ind max concatArray = [(concatArray !! max) !! ind, (concatArray !! max) !! (ind+1), (concatArray !! max) !! (ind+2)]



get4th (_,_,_,a) = a

takeOnlyArray :: [[String]] -> (Int, Int, Int, [[String]]) -> [[String]]
takeOnlyArray str input = [str !! 0 ++ ((get4th input) !! 0), str !! 1 ++ ((get4th input) !! 1), str !! 2 ++ ((get4th input) !! 2)]

--takeOnlyArray input = L.map (\x -> x !! 0) input


-- I want to take the 4th element from the tuple
-- For all the items in the list.


getCombinedArrays :: [[String]] -> [[String]] -> [(Int, Int, Int, [[String]])]
getCombinedArrays arrays strings = map ((foldl getArrays (0, 2, 0, arrays))) strings



getArrays :: (Int, Int, Int, [[String]]) -> String -> (Int, Int, Int, [[String]])
getArrays (ind, max, blankCount, arrays) str =
  if str == "" then
    if blankCount == 3 then
        (ind+1, max, 0, arrays)
    else
        (ind, max, blankCount+1, arrays)
  else
    (ind+1, max, blankCount, (L.take (ind) arrays) ++ [((arrays !! ind) ++ [str])] ++ (L.take (max-(ind)) (reverse arrays)))


-- else
-- (ind+1, max, blankCount+1, (L.take (ind) arrays) ++ ((arrays !! ind) ++ [str]) ++ (L.take (max-(ind+1)) (reverse arrays)))


-- getArrays :: (Int, Int, Int, [[String]]) -> String -> (Int, Int, Int, [[String]])
-- getArrays (ind, max, blankCount, arrays) str = (ind, max, blankCount, arrays)

parseInput :: [String] -> [[String]]
parseInput input = L.map (splitOn " ") (L.map (L.filter (/=']')) (L.map (L.filter (/='[')) input))





-- L.map (L.filter (not . \c -> c == ""))
