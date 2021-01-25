let str = React.string;

let difficultyToHumanReadable = difficulty => {
  switch (difficulty) {
  | 1 | 2 | 3 => "Easy"
  | 4 | 5 | 6 => "Medium"
  | 7 | 8 | 9 | 10 => "Hard"
  | _ => ""
  };
};

let timeToHumanReadable = time => {
  switch (time) {
  | 1 | 2 | 3 => "Quick"
  | 4 | 5 | 6 => "Medium"
  | 7 | 8 | 9 | 10 => "Long"
  | _ => ""
  };
};

let showProject = (maybeProject: option(Types.projectData)) =>
  switch (maybeProject) {
  | Some(project) =>
    <Anchor target={"/projects/" ++ project.id}> project.name->str </Anchor>
  | None => React.null
  };

[@react.component]
let make =
    (
      ~id,
      ~name,
      ~content,
      ~experience,
      ~difficulty,
      ~time,
      ~maybeProject=None,
    ) => {
  <div className="p-4 border-2 rounded-sm">
    <Heading> name->str </Heading>
    content->str
    {showProject(maybeProject)}
    // " - "->str
    // <a href=url target="_blank"> "See"->str </a>
    <Anchor target={"/tasks/" ++ id}>
      <Button onClick={_ => ()}> "See more"->str </Button>
    </Anchor>
    <div>
      {difficultyToHumanReadable(difficulty)->str}
      {timeToHumanReadable(time)->str}
      <Heading size=Small> "Experience: "->str </Heading>
      {(Js.Int.toString(experience) ++ " xp")->str}
      // <Heading size=Small> "Rewards: "->str </Heading>
    </div>
  </div>;
};
