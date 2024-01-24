use std::path::PathBuf;
use anyhow::Result;

use register_machine::Command;
use clap::Parser;

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
    let commands: Vec<_> = text.trim().split('\n').map(Command::de).collect();
    for c in &commands {
	log::debug!("{:?}", c);
    }
    Ok(())
}
