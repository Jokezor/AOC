import Data.Char

main :: IO ()
main = do
  s <- readFile "input.txt"
  let elvesCalories = lines s ++ [""]
  let (maxCaloriesSum, _) = getMaxCalories elvesCalories
  print maxCaloriesSum

getMaxCalories :: [String] -> (Int, Int)
getMaxCalories lines = foldl maxCalories (0, 0) lines

maxCalories :: (Int, Int) -> String -> (Int, Int)
maxCalories (maxCaloriesSum, caloriesSum) str =
  if str == "" then (max maxCaloriesSum caloriesSum, 0)
  else
      (maxCaloriesSum, caloriesSum + (read str::Int))


