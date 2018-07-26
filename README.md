```
git clone https://github.com/aantron/repromise.git
git clone https://github.com/aantron/repromise_lwt.git
cd repromise
opam pin add -y repromise .
opam install -y lwt
cd ../repromise_lwt
dune exec test/test.exe
```

This should print `Tick!` five times, wait for one second, then print a few more messages. See `test/test.re` for the program.

The example creates a Repromise-aware `sleep` function by wrapping `Lwt_unix.sleep`, then exercises it a little bit.
