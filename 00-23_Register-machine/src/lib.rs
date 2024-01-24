#[derive(Debug, PartialEq)]
pub enum Command {
    Step { index: usize },
    Transfer { src: usize, dst: usize },
    Zero { index: usize },
    Jump { a: usize, b: usize, q: usize },
}

impl Command {
    pub fn step(index: usize) -> Command {
        Command::Step { index }
    }
    pub fn transfer(src: usize, dst: usize) -> Command {
        Command::Transfer { src, dst }
    }
    pub fn zero(index: usize) -> Command {
        Command::Zero { index }
    }
    pub fn jump(a: usize, b: usize, q: usize) -> Command {
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
	log::trace!("Deserializing {:?} as Command", s);
        let key = s.chars().next().expect("Expected at least 1 char.");
        let args: Vec<usize> = s[2..]
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
