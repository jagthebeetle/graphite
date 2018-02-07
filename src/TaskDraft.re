type state = {
  nextId: int,
  editingId: string,
  editingDependencies: list(Task.t)
};

type action =
  | EditId(string);

let component = ReasonReact.reducerComponent("TaskDraft");

let maybeConflictMessage = (conflict) =>
  switch (conflict) {
  | None => <div></div>;
  | Some(error) => <div className="conflict">(Util.str(error))</div>;
  };

let make = (~conflict, ~draftSubmit: (Task.t => unit), _children) => {
  let click = (_event, {ReasonReact.state}) => {
    draftSubmit({
      id: state.editingId, dependencies: state.editingDependencies
    });
  };
  {
    ...component,
    initialState: () => {
      nextId: 0,
      editingId: "",
      editingDependencies: []
    },
    reducer: (action, state) =>
      switch (action) {
      | EditId(text) => ReasonReact.Update({...state, editingId: text});
      },
    render: (self) => {
      <div className="draft">
        (maybeConflictMessage(conflict))
        <input value=self.state.editingId placeholder="Task name"
          onChange=(event => self.send(EditId(
            ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
          )))/>
        <button onClick=self.handle(click)>(Util.str("Add Task"))</button>
      </div>
    }
  }
};
