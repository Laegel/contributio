let str = React.string

module RevokeLinkedAccount = %graphql(`
    mutation revokeLinkedAccount($originId: Int!) {
      revokeLinkedAccount(originId: $originId)
    }
   `)

let trigger = (originId, onDone) =>
  Client.instance.mutate(~mutation=module(RevokeLinkedAccount), {originId: originId})
  ->Promise.Promise.then_(result =>
    Js.Promise.resolve(
      switch result {
      | Ok(_) =>
        onDone()
        React.null
      | Error(_) => React.null
      },
    )
  )
  ->ignore