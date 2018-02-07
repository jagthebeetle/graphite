type state = {
  conflict: option(string),
  tasks: list(Task.t)
};

type action =
  | DeleteTask(Task.t)
  | SubmitTask(Task.t);

let component = ReasonReact.reducerComponent("App");

let taskExists = (task: Task.t) => List.find((existing: Task.t) => existing.id === task.id);
let conflictMessage = (id) => id ++ " already exists.";

let make = (_children) => {
  ...component,
  initialState: () => {
    conflict: None,
    tasks: []
  },
  reducer: (action, state) =>
    switch (action) {
    | DeleteTask(task) =>
      let tasks = List.filter(existing => existing !== task, state.tasks);
      ReasonReact.Update({...state, tasks});
    | SubmitTask(task) => 
      switch(taskExists(task, state.tasks)) {
      | exception Not_found =>
        ReasonReact.Update({conflict: None, tasks: [task, ...state.tasks]});
      | _ => ReasonReact.Update({...state, conflict: Some(conflictMessage(task.id))});
      }
    },
  render: (self) => {
    <div>
      <TaskList tasks=self.state.tasks />
      <TaskDraft
        conflict=self.state.conflict
        draftSubmit=(task => self.send(SubmitTask(task)))
      />
    </div>
  }
};
