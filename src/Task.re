type t = {
  id: string,
  dependencies: list(t)
};


module TaskCard = {

  let component = ReasonReact.statelessComponent("TaskCard");
  let make = (~task, _children) => {
    ...component,
    render: _self => {
      <div className="card">
        <span className="id">(Util.str("Task "))<em>(Util.str(task.id))</em></span>
        <div className="dependencies">(Util.str("Dependencies go here"))</div>
      </div>;
    }
  };
};