let str = React.string;

type names =
  | ExternalLink
  | Import
  | Github
  | Gitlab
  | Link
  | Pencil
  | Trash
  | User;

type sizes =
  | Small
  | Medium
  | Large
  | ExtraLarge
  | EvenLarger(int);

type colors =
  | Default
  | Black
  | White
  | Red
  | Green
  | Blue
  | Custom(string);

[@react.component]
let make = (~name: names, ~size: sizes=Small, ~color: colors=Default) => {
  <i
    className={
      (
        switch (name) {
        | ExternalLink => "cil-external-link"
        | Import => "cil-arrow-thick-from-top"
        | Github => "cib-github"
        | Gitlab => "cib-gitlab"
        | Link => "cil-link"
        | Pencil => "cil-pencil"
        | Trash => "cil-trash"
        | User => "cil-user"
        }
      )
      ++ " "
      ++ (
        switch (size) {
        | Small => "text-sm"
        | Medium => "text-base"
        | Large => "text-lg"
        | ExtraLarge => "text-xl"
        | EvenLarger(modifier) =>
          "text-" ++ Js.Int.toString(modifier) ++ "xl"
        }
      )
      ++ " "
      ++ (
        switch (color) {
        | Default => "text-current"
        | Black => "text-black"
        | White => "text-white"
        | Red => "text-red-800"
        | Green => "text-green-800"
        | Blue => "text-blue-800"
        | Custom(modifier) => "text-" ++ modifier
        }
      )
    }
  />;
};
