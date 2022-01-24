use std::io;


fn guess_num() {
    println!("Guess the number.");
    println!("Input your guess: ");

    let mut guess: String = String::new();

    io::stdin()
        .read_line(&mut guess)
        .expect("Failed to read line");
    println!("Your guessed number is: {}.", guess);
}


fn main() {
    guess_num();
}
