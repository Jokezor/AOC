import Data.Char
import Data.List
import Data.Ord

main :: IO ()
main = do
  s <- readFile "input.txt"
  let elvesCalories = lines s ++ [""]
  let (_, calories) = sumElvesCalories elvesCalories
  let topElves = sum (take 3 (sortBy (comparing Down) calories))
  print topElves

sumElvesCalories :: [String] -> (Int, [Int])
sumElvesCalories lines = foldl sumCalories (0, []) lines

sumCalories :: (Int, [Int]) -> String -> (Int, [Int])
sumCalories (caloriesSum, calories) str =
  if str == "" then (0, calories ++ [caloriesSum])
  else
      ((caloriesSum + (read str::Int)), calories)


