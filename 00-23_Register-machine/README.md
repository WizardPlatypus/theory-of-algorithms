# What dis

This is an interpreter for a very basic (Register Machine)[https://en.wikipedia.org/wiki/Register_machine].

There are 4 operations awailable:
- `S X` - STEP X - increase value in register X by 1.
- `T X Y` - TRANSFER X Y - transfer value from register X to register Y.
- `Z X` - ZERO X - make value in register X equal 0.
- `J X Y Q` - JUMP X Y Q - if value in register X is equal to value in register Y, go to instruction Q.

# Usage

This project is built with (`cargo`)[]:
```bash
cargo build
```

To run the project and see some help:
```bash
cargo run -- --help
```

To run, the project requires a path to the file containing the program, and any number of initial register states, i.e.:
```bash
cargo run -- samples/06_x-y.txt 5 3
```

To see a few log messages:
```bash
RUST_LOG=trace cargo run -- samples/06_x-y.txt 5 3
```

The current number of operations total is capped at 100, to help exit infinite loops and prevent too large outputs.
