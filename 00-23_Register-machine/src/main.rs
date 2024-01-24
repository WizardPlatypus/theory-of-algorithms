use anyhow::Result;
use std::path::PathBuf;

use clap::Parser;
use register_machine::Command;

#[derive(Parser, Debug)]
struct Args {
    /// File containing the program
    file: PathBuf,
    /// Register values
    registers: Vec<usize>,
}

fn main() -> Result<()> {
    pretty_env_logger::init();

    let args = Args::parse();
    // load file
    log::trace!("Loading file {:?}...", args.file);
    let text = std::fs::read_to_string(&args.file)?;
    log::trace!("Parsing file {:?}...", args.file);
    let commands: Vec<_> = text
        .trim()
        .split('\n')
        .map(|x| Command::try_from(x).expect("Failed to parse a Command"))
        .collect();
    // find register count
    let mut last = 0;
    for c in &commands {
        match c {
            Command::Step { index } => {
                last = std::cmp::max(last, *index);
            }
            Command::Transfer { src, dst } => {
                last = std::cmp::max(last, *src);
                last = std::cmp::max(last, *dst);
            }
            Command::Zero { index } => {
                last = std::cmp::max(last, *index);
            }
            Command::Jump { a, b, q: _ } => {
                last = std::cmp::max(last, *a);
                last = std::cmp::max(last, *b);
            }
        }
    }
    // filling in the registers
    let mut registers = Vec::with_capacity(last + 1);
    for i in 0..=last {
        let r = if i < args.registers.len() {
            args.registers[i]
        } else {
            0
        };
        registers.push(r);
    }
    let mut cursor = 1;
    let mut count = 0;
    let mut jump = 0;

    print!("| cursor | count | command |");
    for i in 0..registers.len() {
        print!(" R{} |", i);
    }
    println!();

    print!("|-|-|-|");
    for _ in 0..registers.len() {
        print!("-|");
    }
    println!();

    display(cursor, count, None, &registers);

    loop {
        count += 1;
        if jump == 0 {
            cursor += 1;
        } else {
            cursor = jump;
            jump = 0;
        }
        if cursor > commands.len() || count > 100 {
            break;
        }
        match &commands[cursor - 1] {
            Command::Step { index } => registers[*index] += 1,
            Command::Transfer { src, dst } => registers[*dst] = registers[*src],
            Command::Zero { index } => registers[*index] = 0,
            Command::Jump { a, b, q } => {
                if registers[*a] == registers[*b] {
                    jump = *q;
                    continue;
                }
            }
        }
        display(cursor, count, Some(&commands[cursor - 1]), &registers);
    }
    Ok(())
}

fn display(cursor: usize, count: usize, command: Option<&Command>, registers: &Vec<usize>) {
    if let Some(c) = command {
	print!("| {}) | [{}] | {} |", cursor, count, c);
    } else {
	print!("| {}) | [{}] | - |", cursor, count);
    }
    for r in registers {
        print!(" {} |", r);
    }
    println!();
}
