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
}

impl std::fmt::Display for Command {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Command::Step { index } => write!(f, "S({})", index),
            Command::Transfer { src, dst } => write!(f, "T({},{})", src, dst),
            Command::Zero { index } => write!(f, "Z({})", index),
            Command::Jump { a, b, q } => write!(f, "J({},{},{})", a, b, q),
        }
    }
}

impl<'a> std::convert::TryFrom<&'a str> for Command {
    type Error = &'a str;
    fn try_from(value: &'a str) -> Result<Command, Self::Error> {
        let key = value.chars().next().ok_or(value)?;
        let mut args: Vec<usize> = Vec::new();
        for x in value[2..].split(' ') {
            args.push(x.parse().map_err(|_| value)?);
        }
        if key == 'S' {
            Ok(Command::step(args[0]))
        } else if key == 'T' {
            Ok(Command::transfer(args[0], args[1]))
        } else if key == 'Z' {
            Ok(Command::zero(args[0]))
        } else if key == 'J' {
            Ok(Command::jump(args[0], args[1], args[2]))
        } else {
            log::debug!("{:?} is not a Command", value);
            Err(value)
        }
    }
}

#[cfg(test)]
mod tests {
    #[test]
    pub fn try_from_works() {
        use crate::Command;
        assert!(Command::try_from("S 1").unwrap() == Command::step(1));
        assert!(Command::try_from("T 2 3").unwrap() == Command::transfer(2, 3));
        assert!(Command::try_from("Z 4").unwrap() == Command::zero(4));
        assert!(Command::try_from("J 1 2 3").unwrap() == Command::jump(1, 2, 3));
    }
}
