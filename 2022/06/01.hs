import Data.Char
import Data.Set as S
import Data.List as L

main :: IO ()
main = do
  s <- readFile "input.txt"
  let input = L.filter (not . isSpace) s
  print input

  -- Part 1
  let startPacket = getStartPacket 4 0 input
  print startPacket

  -- Part 2
  let startMessage = getStartPacket 14 0 input
  print startMessage


removeFirst :: [a] -> [a]
removeFirst = \myList ->
  case myList of
    [] -> [] -- if the list is empty, return empty list
    x:xs -> xs -- split head and return remaining list


getStartPacket :: Int -> Int -> String -> Int
getStartPacket num_distinct ind str = 
  if S.size (S.fromList (L.take num_distinct str)) == num_distinct then
      ind + num_distinct
  else
      getStartPacket num_distinct (ind+1) (removeFirst str)
