Js.log("Hello world");

module UserList = {
  type t = {
    id: Credt.Util.id,
    name: string,
    email: string,
    age: int,
  };

  type update =
    | SetEmail(string)
    | SetName(string)
    | SetAge(int);

  let reducer = user =>
    fun
    | SetEmail(email) => ({...user, email}, SetEmail(user.email))
    | SetName(name) => ({...user, name}, SetName(user.name))
    | SetAge(age) => ({...user, age}, SetAge(user.age));

  include Credt.List.Make({
    type nonrec t = t;
    type nonrec update = update;
    let getId = u => u.id;
    let moduleId = "UserList" |> Credt.Util.idOfString;
    let reducer = reducer;
  });
};

let makeUser = i => {
  UserList.id: Credt.Util.makeId(),
  name: "Name" ++ (i |> string_of_int),
  email: "email@" ++ (i |> string_of_int),
  age: i * 2,
};

let userStdList = Stdlib.List.init(10, makeUser);
Js.log2("userStdList", userStdList);

let me = {
  UserList.id: Credt.Util.makeId(),
  name: "Andreas",
  email: "andreas@eldh.co",
  age: 35,
};

let miniMe = {
  UserList.id: Credt.Util.makeId(),
  name: "Sixten",
  email: "sixten@eldh.co",
  age: 2,
};

[
  UserList.Append(me),
  Update(me.id, SetEmail("a@eldh.co")),
  UserList.Append(miniMe),
  Update(miniMe.id, SetName("Sixten Eldh")),
]
|> UserList.addToTransaction;
[@react.component]
let make = () => {
  let userStdList = userStdList->Belt.List.toArray;
  <div>
    <header> {React.string("Hello React")} </header>
    {Belt.Array.mapWithIndex(userStdList, (i, user) =>
       <li>
         <React.Fragment key={i->string_of_int}>
           {React.string("name: " ++ user.name)}
           {" " |> React.string}
           {React.string("email: " ++ user.email)}
           {" " |> React.string}
           {React.string("age: " ++ user.age->string_of_int)}
         </React.Fragment>
       </li>
     )
     |> React.array}
  </div>;
};
