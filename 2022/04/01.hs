import Data.List as L
import Data.List.Split
import Data.Char
import Data.Set as S

main :: IO ()
main = do
  s <- readFile "input.txt"
  let sLines = lines s
  print sLines
  let strRanges = L.map getStrRanges sLines
  print strRanges
  let intRanges = L.map strRangesToIntRanges strRanges
  print intRanges

  -- Part 1
  let subsets = L.foldl countRangeSubsets 0 intRanges
  print subsets

  -- Part 2
  let subsets = L.foldl countOverlappingSets 0 intRanges
  print subsets

countOverlappingSets :: Int -> [[Int]] -> Int
countOverlappingSets count [first, second]
  | S.fromList first `S.disjoint` S.fromList second = count
  | S.fromList second `S.disjoint` S.fromList first = count
  | otherwise = count + 1

countRangeSubsets :: Int -> [[Int]] -> Int
countRangeSubsets count [first, second]
  | S.fromList first `S.isSubsetOf` S.fromList second = count + 1
  | S.fromList second `S.isSubsetOf` S.fromList first = count + 1
  | otherwise = count

getStrRanges :: String -> [String]
getStrRanges str = (splitOn "," str)

strRangesToIntRanges :: [String] -> [[Int]]
strRangesToIntRanges str = L.map (strRangeToIntRange . (splitOn "-")) str

strRangeToIntRange :: [String] -> [Int]
strRangeToIntRange [first, second] = [(read first::Int)..(read second::Int)]
