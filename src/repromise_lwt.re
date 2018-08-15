module Lwt_sequence = Lwt_sequence;

let repromiseToLwt = repromise => {
  let (lwtPromise, lwtResolver) = Lwt.wait();
  repromise |> Repromise.wait(value => Lwt.wakeup_later(lwtResolver, value));
  lwtPromise;
};

let lwtToRepromise = lwtPromise => {
  let (repromise, resolveRepromise) = Repromise.make();
  Lwt.on_success(lwtPromise, value => resolveRepromise(Result.Ok(value)));
  Lwt.on_failure(lwtPromise, exn => resolveRepromise(Result.Error(exn)));
  repromise;
};

open Lwt.Infix;

let (shouldStop, notifyShouldStop) = Lwt.wait();

let run = () => {
  Lwt_main.enter_iter_hooks |> Lwt_sequence.add_r(() =>
    if(Repromise.ReadyCallbacks.callbacksPending()) {
      Lwt.async(() =>
        Lwt_main.yield() >>= () => {
          Repromise.ReadyCallbacks.snapshot()
          |> Repromise.ReadyCallbacks.call;
          Lwt.return_unit;
        })
    })
  |> ignore;

  Lwt_main.run(shouldStop);
};

let stop = () =>
  Lwt.wakeup_later(notifyShouldStop, ());
