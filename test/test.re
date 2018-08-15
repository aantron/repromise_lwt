/* The type of this is float => Repromise.t(unit). */
let sleep = seconds =>
  Lwt_unix.sleep(seconds)
  |> Repromise_lwt.lwtToRepromise
  |> Repromise.map(fun
  | Ok() => ()
  | Error(_) => assert false);

let rec spamDuringIO = count =>
  if(count < 1) {
    ()
  }
  else {
    /* Defer a print to the next tick, to make sure Repromise_lwt.run is
       actually doing ticks as long as there are callbacks in the queue. */
    Repromise.resolved()
    |> Repromise.wait(() => {
      print_endline("Tick!");
      spamDuringIO(count - 1);
    })
  };

spamDuringIO(5);

let () =
  sleep(1.)
  |> Repromise.wait(() => {
    print_endline("Sleep finished");
    Repromise_lwt.stop();
  });

Repromise_lwt.run();

print_endline("Repromise_lwt.run exited");
