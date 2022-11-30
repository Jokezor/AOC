main = do
  s <- readFile "input.txt"
  let (ind, level) = myFunc s
  print ind

-- Take the numbers and add up.
myFunc :: String -> (Int, Int)
myFunc str = foldl myFuncFold (0, 0) str

myFuncFold :: (Int, Int) -> Char -> (Int, Int)
myFuncFold (ind, level) c =
  if level == -1 then (ind, level)
  else if c == '(' then (ind +1, level + 1)
  else if c == ')' then (ind + 1, level - 1)
  else (ind, level)




