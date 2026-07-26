import "./App.css";
import { useState, useEffect } from "react";

const API = "http://localhost:8081";

function App() {
  const [username, setUsername] = useState("");
  const [loggedIn, setLoggedIn] = useState(false);

  const [allProjects, setAllProjects] = useState([]);
  const [myProjects, setMyProjects] = useState([]);

  const [allDevs, setAllDevs] = useState([]);
  const [skillFilter, setSkillFilter] = useState("");

  const [targetDev, setTargetDev] = useState("");
  const [projectInput, setProjectInput] = useState("");

  const [error, setError] = useState("");

  const filteredDevs = allDevs.filter(
    (d) =>
      skillFilter === "" ||
      (d.skills && d.skills.toLowerCase().includes(skillFilter.toLowerCase())),
  );

  function loadDevelopers() {
    fetch(`${API}/developers`)
      .then((r) => r.json())
      .then((data) => setAllDevs(data));
  }

  function handleAssign() {
    const projectNames = projectInput
      .split(",")
      .map((s) => s.trim())
      .filter(Boolean);

    fetch(`${API}/projects/assign`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        developerName: targetDev,
        projectNames: projectNames,
      }),
    })
      .then((r) => r.text())
      .then((msg) => alert(msg))
      .catch((err) => setError(err.message));
  }

  useEffect(() => {
    fetch(`${API}/projects`)
      .then((r) => r.json())
      .then((data) => setAllProjects(data))
      .catch((err) => console.error(err));
  }, []);

  useEffect(() => {
    if (!loggedIn) return;
    fetch(`${API}/projects/member/${username}`)
      .then((r) => r.json())
      .then((data) => setMyProjects(data));
  }, [loggedIn, username]);

  if (!loggedIn) {
    return (
      <div className="container">
        <h2>Enter your name</h2>
        <input value={username} onChange={(e) => setUsername(e.target.value)} />
        <button
          onClick={() => {
            if (username === "") {
              setError("Insert a name!");
            } else {
              setLoggedIn(true);
              setError("");
            }
          }}
        >
          Enter
        </button>

        {error && (
          <p className="error" color="red">
            {error}
          </p>
        )}
      </div>
    );
  }

  return (
    <div className="container">
      <h1>Hello, {username}</h1>

      <h2>All Projects</h2>
      <table border="1">
        <thead>
          <tr>
            <th>ID</th>
            <th>Name</th>
            <th>Description</th>
            <th>Members</th>
            <th>Manager ID</th>
          </tr>
        </thead>
        <tbody>
          {allProjects.map((p) => (
            <tr key={p.id}>
              <td>{p.id}</td>
              <td>{p.name}</td>
              <td>{p.description}</td>
              <td>{p.members}</td>
              <td>{p.projectManagerId}</td>
            </tr>
          ))}
        </tbody>
      </table>

      <h2>My Projects</h2>
      <ul>
        {myProjects.map((name, i) => (
          <li key={i}>{name}</li>
        ))}
      </ul>

      <h2>Assign Developer to Projects</h2>
      <input
        placeholder="Developer name"
        value={targetDev}
        onChange={(e) => setTargetDev(e.target.value)}
      />
      <input
        placeholder="Project names (comma separated)"
        value={projectInput}
        onChange={(e) => setProjectInput(e.target.value)}
        style={{ width: 300 }}
      />
      <button onClick={handleAssign}>Assign</button>

      <h2>All Developers</h2>
      <button onClick={loadDevelopers}>Load Developers</button>
      <br />
      <input
        placeholder="Filter by skill (e.g. Java)"
        value={skillFilter}
        onChange={(e) => setSkillFilter(e.target.value)}
      />
      <table border="1">
        <thead>
          <tr>
            <th>ID</th>
            <th>Name</th>
            <th>Age</th>
            <th>Skills</th>
          </tr>
        </thead>
        <tbody>
          {filteredDevs.map((d) => (
            <tr key={d.id}>
              <td>{d.id}</td>
              <td>{d.name}</td>
              <td>{d.age}</td>
              <td>{d.skills}</td>
            </tr>
          ))}
        </tbody>
      </table>
      {error && (
        <p className="error" color="red">
          {error}
        </p>
      )}
    </div>
  );
}

export default App;
