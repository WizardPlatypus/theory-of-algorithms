type Nat = u64;

#[derive(Debug, PartialEq)]
pub enum Command {
    Step { index: Nat },
    Transfer { src: Nat, dst: Nat },
    Zero { index: Nat },
    Jump { a: Nat, b: Nat, q: Nat },
}

impl Command {
    pub fn step(index: Nat) -> Command {
        Command::Step { index }
    }
    pub fn transfer(src: Nat, dst: Nat) -> Command {
        Command::Transfer { src, dst }
    }
    pub fn zero(index: Nat) -> Command {
        Command::Zero { index }
    }
    pub fn jump(a: Nat, b: Nat, q: Nat) -> Command {
        Command::Jump { a, b, q }
    }

    pub fn ser(&self) -> String {
        use Command::{Jump, Step, Transfer, Zero};
        match self {
            Step { index } => format!("S {}", index),
            Transfer { src, dst } => format!("T {} {}", src, dst),
            Zero { index } => format!("Z({})", index),
            Jump { a, b, q } => format!("J {} {} {}", a, b, q),
        }
    }

    pub fn de(s: &str) -> Option<Command> {
        let key = s.chars().next().expect("Expected at least 1 char.");
        let args: Vec<Nat> = s[2..]
            .split(' ')
            .map(|x| x.parse().expect("Failed to parse as number"))
            .collect();
        if key == 'S' {
            Some(Command::step(args[0]))
        } else if key == 'T' {
            Some(Command::transfer(args[0], args[1]))
        } else if key == 'Z' {
            Some(Command::zero(args[0]))
        } else if key == 'J' {
            Some(Command::jump(args[0], args[1], args[2]))
        } else {
            None
        }
    }
}

fn main() {
    let mut buffer = String::new();
    print!("Enter number of registers: ");
    std::io::stdin()
        .read_line(&mut buffer)
        .expect("Failed to read number of registers");

    let n: usize = buffer.parse().expect("Failed to parse n");
    let mut r: Vec<Nat> = Vec::with_capacity(n);
    for i in 0..n {
        print!("Enter initial state of register #{}.", i);
        std::io::stdin()
            .read_line(&mut buffer)
            .expect("Failed to read register contents.");
        r.push(buffer.parse().expect("Failed to parse register contents"));
    }

    let mut q: Vec<Command> = Vec::new();
    println!("Enter commands:");
    for line in std::io::stdin().lines() {
        println!("[debug] read {:?}", line);
        let command = Command::de(line.unwrap().as_str()).expect("Failed to deserialize Command.");
        q.push(command);
    }
}

#[cfg(test)]
mod tests {
    #[test]
    pub fn de_works() {
        use crate::Command;
        assert!(Command::de("S 1").unwrap() == Command::step(1));
        assert!(Command::de("T 2 3").unwrap() == Command::transfer(2, 3));
        assert!(Command::de("Z 4").unwrap() == Command::zero(4));
        assert!(Command::de("J 1 2 3").unwrap() == Command::jump(1, 2, 3));
    }
}
