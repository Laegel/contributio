let str = React.string;

let difficultyToHumanReadable = difficulty => {
  switch (difficulty) {
  | 1
  | 2
  | 3 => "Easy"
  | 4
  | 5
  | 6 => "Medium"
  | 7
  | 8
  | 9
  | 10 => "Hard"
  | _ => ""
  };
};

let timeToHumanReadable = time => {
  switch (time) {
  | 1
  | 2
  | 3 => "Quick"
  | 4
  | 5
  | 6 => "Medium"
  | 7
  | 8
  | 9
  | 10 => "Long"
  | _ => ""
  };
};

let showProject = (maybeProject: option(Types.projectData)) =>
  switch (maybeProject) {
  | Some(project) =>
    <Anchor className="text-primary" target={"/projects/" ++ project.id}>
      project.name->str
    </Anchor>
  | None => React.null
  };

[@react.component]
let make =
    (
      ~id,
      ~name,
      ~content,
      // ~url,
      ~experience,
      ~difficulty,
      ~time,
      ~maybeProject=None,
    ) => {
  <div className="card px-4 pb-4 pt-2 border-2 rounded-sm relative">
    <Anchor target={"/tasks/" ++ id} className="text-primary">
      <Heading> name->str </Heading>
    </Anchor>
    <div className="text-xs mt-1"> {showProject(maybeProject)} </div>
    <div className="absolute right-2 top-2">
      <a href="" target="_blank">
        <Button> <Icon name=ExternalLink /> </Button>
      </a>
    </div>
    <div className="text-current my-3">
      {Js.String2.substring(content, ~from=0, ~to_=60)->str}
    </div>
    <div>
      <span
        className="text-current rounded-sm border-green-500 border-2 p-0.5 m-0.5">
        <Icon name=Lightbulb />
        {difficultyToHumanReadable(difficulty)->str}
      </span>
      <span
        className="text-current rounded-sm border-green-500 border-2 p-0.5 m-0.5">
        <Icon name=Timer />
        {timeToHumanReadable(time)->str}
      </span>
    </div>
    <hr className="my-2" />
    <div> <Experience amount={Js.Int.toString(experience)} /> </div>
  </div>;
};
