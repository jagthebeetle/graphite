let component = ReasonReact.statelessComponent("TaskList");

let make = (~tasks: list(Task.t), _children) => {
  ...component,
  render: _self => {
    let taskCards = List.map((task: Task.t) => <Task.TaskCard key=task.id task=task/>, tasks);
    <div className="tasklist">
      (ReasonReact.arrayToElement(Array.of_list(taskCards)))
    </div>
  }
};