import logo from "./logo.svg";
import "./App.css";
import { useState, useEffect } from "react";

const API = "https://localhost:7134";

function App() {
  const [username, setUsername] = useState("");
  const [userId, setUserId] = useState(null);
  const [lastUser, setLastUser] = useState("");
  const [allTasks, setAllTasks] = useState([]);
  const [loggedIn, setLoggedIn] = useState(false);
  const [count, setCount] = useState(0);
  const [error, setError] = useState("");

  function login() {
    if (username === "") {
      setError("Insert a username!");
      return;
    }

    setError("");
    fetch(`${API}/login/${username}`)
      .then((r) => {
        if (!r.ok) {
          return r.text().then((msg) => {
            setError(msg);
          });
        }
        return r.json();
      })
      .then((user) => {
        if (user) {
          setUsername(user.username);
          setUserId(user.id);
          setLoggedIn(true);
        }
      })
      .catch((err) => setError(err.message));
  }

  function moveTask(task, newStatus) {
    fetch(`${API}/tasks`, {
      method: "PUT",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        taskId: task.id,
        userId: userId,
        status: newStatus,
        timeStamp: new Date().toISOString(),
      }),
    })
      .then((r) => {
        if (r.ok) setCount((c) => c + 1);
      })
      .catch((err) => console.error(err));
  }

  useEffect(() => {
    if (!loggedIn) return;

    const fetchTasks = () => {
      fetch(`${API}/tasks`)
        .then((r) => r.json())
        .then((data) => setAllTasks(data))
        .catch((err) => console.error(err));
    };

    fetchTasks();
    const interval = setInterval(fetchTasks, 3000);
    return () => clearInterval(interval);
  }, [loggedIn]);

  if (!loggedIn) {
    return (
      <div className="container">
        <h2>Enter your name</h2>
        <input value={username} onChange={(e) => setUsername(e.target.value)} />
        <button onClick={login}>Enter</button>

        {error && (
          <p className="error" color="red">
            {error}
          </p>
        )}
      </div>
    );
  }

  const statuses = ["todo", "in_progress", "done"];
  const statusLabels = {
    todo: "To Do",
    in_progress: "In Progress",
    done: "Done",
  };

  return (
    <div className="container">
      <h1>Hello, {username}</h1>
      <p>
        Tasks moved this session: <strong>{count}</strong>
      </p>

      <div style={{ display: "flex", gap: "20px" }}>
        {statuses.map((status) => (
          <div
            key={status}
            style={{
              flex: 1,
              border: "1px solid #ddd",
              padding: "10px",
              borderRadius: "8px",
              minHeight: "200px",
            }}
          >
            <h3>{statusLabels[status]}</h3>
            {allTasks
              .filter((t) => t.status === status)
              .map((t) => (
                <div
                  key={t.id}
                  title={
                    t.lastUpdatedByName
                      ? `Last updated by ${t.lastUpdatedByName}`
                      : "Not yet moved"
                  }
                  style={{
                    border: "1px solid #ccc",
                    padding: "8px",
                    marginBottom: "8px",
                    borderRadius: "4px",
                    backgroundColor: "#fafafa",
                  }}
                >
                  <strong>{t.title}</strong>
                  <div
                    style={{
                      marginTop: "6px",
                      display: "flex",
                      gap: "4px",
                      flexWrap: "wrap",
                    }}
                  >
                    {statuses
                      .filter((s) => s !== status)
                      .map((s) => (
                        <button key={s} onClick={() => moveTask(t, s)}>
                          → {statusLabels[s]}
                        </button>
                      ))}
                  </div>
                </div>
              ))}
          </div>
        ))}
      </div>
    </div>
  );
}

export default App;
