use std::fs;

fn remove_ws(s: &String) -> String {
    s.chars().filter(|c| !c.is_whitespace()).collect()
}

fn is_triangle(a : i32, b : i32, c : i32) -> bool {
    a + b > c && a + c > b && c + b > a
}

fn part_1(contents : String) -> i32 {

    let clean_contents = contents.lines();

    let mut num_triangles = 0;

    for content in clean_contents {
        let mut ints = content.split_whitespace();
        let (a, b, c) = (
            ints.next().expect("i32").parse::<i32>().unwrap(),
            ints.next().expect("i32").parse::<i32>().unwrap(),
            ints.next().expect("i32").parse::<i32>().unwrap(),
        );
        num_triangles += is_triangle(a, b, c) as i32;
        println!("a: {}, b: {}, c: {}", a, b, c);
    }

    num_triangles
}

fn part_2(contents : String) -> i32 {

    let mut clean_contents = contents.lines();

    let n = clean_contents.clone().count();

    let mut num_triangles = 0;
    let mut i = 0;

    while i < n - 2 {
        // Parse in pairs of 3.
        let mut ints1 = clean_contents.next().expect("Should be split by 3").split_whitespace();
        let (a1, a2, a3) = (
            ints1.next().expect("i32").parse::<i32>().unwrap(),
            ints1.next().expect("i32").parse::<i32>().unwrap(),
            ints1.next().expect("i32").parse::<i32>().unwrap(),
        );
        let mut ints2 = clean_contents.next().expect("Should be split by 3").split_whitespace();
        let (b1, b2, b3) = (
            ints2.next().expect("i32").parse::<i32>().unwrap(),
            ints2.next().expect("i32").parse::<i32>().unwrap(),
            ints2.next().expect("i32").parse::<i32>().unwrap(),
        );
        let mut ints3 = clean_contents.next().expect("Should be split by 3").split_whitespace();
        let (c1, c2, c3) = (
            ints3.next().expect("i32").parse::<i32>().unwrap(),
            ints3.next().expect("i32").parse::<i32>().unwrap(),
            ints3.next().expect("i32").parse::<i32>().unwrap(),
        );
        num_triangles += is_triangle(a1, b1, c1) as i32;
        num_triangles += is_triangle(a2, b2, c2) as i32;
        num_triangles += is_triangle(a3, b3, c3) as i32;
        //println!("a1: {}, b1: {}, c1: {}", a1, b1, c1);
        i += 3;
    }

    num_triangles
}


fn main() {
    // First test with example
    let example_contents = fs::read_to_string("src/example_input.txt")
        .expect("Should have read file.");

    let ex_1 = part_1(example_contents.clone());

    assert!(ex_1 == 2);

    // Now run with input
    let contents = fs::read_to_string("src/input.txt")
        .expect("Should have read file.");

    let ans_1 = part_1(contents.clone());
    println!("part 1: {}", ans_1);

    // Part 2
    let example_contents_2 = fs::read_to_string("src/example_input_2.txt")
        .expect("Should have read file.");

    let ex_2 = part_2(example_contents_2.clone());

    println!("part 2 ex: {}", ex_2);
    assert!(ex_2 == 6);

    let ans_2 = part_2(contents.clone());
    println!("part 2: {}", ans_2);

}
