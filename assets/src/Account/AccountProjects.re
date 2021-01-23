let str = React.string;

module GetUserProjects = [%graphql
  {|
    query getUserProjects {
      my {
        projects {
          id
          name
          url
          description
        }
      }
    }
|}
];

[@react.component]
let make = () => {
  <div>
    <h1> "My Projects"->str </h1>
    <Anchor target="/account/import/projects">
      "Import Repositories"->str
    </Anchor>
    {switch (GetUserProjects.use()) {
     | {loading: true} => "Loading..."->React.string
     | {data: Some({my}), loading: false} =>
       <div className="grid grid-cols-3 gap-4">
         {switch (my.projects) {
          | [||] => "No projects yet!"->str
          | values =>
            values
            ->Belt.Array.map(project =>
                <div>
                  <Project
                    key={project.id}
                    id={project.id}
                    name={project.name}
                    description={project.description}
                    url={project.url}
                  />
                  <Anchor
                    target={
                      "/account/import/projects/" ++ project.id ++ "/tasks/"
                    }>
                    "Import Issues from this Repository"->str
                  </Anchor>
                </div>
              )
            ->React.array
          }}
       </div>
     /* {switch my.projects {
         | None => "No projects yet!"->str
        | Some(items) => items
        ->Belt.Array.map(project =>
            <Project
              key={project.name}
              name={project.name}
              url={project.url}
            />
          )
        ->React.array
        };} */
     | {data: None} => "No projects yet!"->str
     }}
  </div>;
};
