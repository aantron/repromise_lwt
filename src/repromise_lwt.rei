let repromiseToLwt: Repromise.t('a) => Lwt.t('a);
let lwtToRepromise: Lwt.t('a) => Repromise.t(Result.result('a, exn));

let run: unit => unit;
let stop: unit => unit;
