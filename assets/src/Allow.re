let str = React.string;

module RequestAccessToken = [%graphql
  {|
    query requestAccessToken($originId: Int!, $code: String!) {
      requestAccessToken(originId: $originId, code: $code) {
        accessToken
      }
    }
   |}
];

[@react.component]
let make = (~code) => {
  switch (RequestAccessToken.use({originId: 1, code})) {
  | {data: Some(response)} =>
    let accessToken =
      Js.Dict.unsafeGet(
        Url.parseQueryArgs(response.requestAccessToken.accessToken),
        "access_token",
      );

    if (Session.isConnected()) {
      <LinkAccount accessToken onDone={() => Window.close()} />;
    } else {
      <CreateAccount
        accessToken
        onDone={() => {
          Window.postMessage("link:success");
          Window.close();
        }}
      />;
    };

  | {data: None} => <div> "Loading..."->str </div>
  };
};
