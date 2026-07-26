import "./App.css";
import { useState, useEffect } from "react";
import { BrowserRouter, Routes, Route, useNavigate } from "react-router-dom";

const API = "https://localhost:7217";

function App() {
  const [userId, setUserId] = useState(0);
  const [userName, setUserName] = useState("");
  const [scores, setScores] = useState({});

  return (
    <BrowserRouter>
      <Routes>
        <Route
          path="/"
          element={
            <LoginPage
              setUserId={setUserId}
              userName={userName}
              setUserName={setUserName}
              setScores={setScores}
            />
          }
        />
        <Route
          path="/ProfilePage"
          element={
            <ProfilePage
              scores={scores}
              setScores={setScores}
              userId={userId}
              userName={userName}
            />
          }
        />
        <Route path="/SummaryPage" element={<SummaryPage scores={scores} />} />
        <Route
          path="/SessionLogPage"
          element={<SessionLogPage userId={userId} />}
        />
      </Routes>
    </BrowserRouter>
  );
}

function SessionLogPage({ userId }) {
  const navigate = useNavigate();
  const [sessions, setSessions] = useState([]);

  useEffect(() => {
    fetch(`${API}/profile/sessions/${userId}`)
      .then((r) => r.json())
      .then((data) => {
        if (data) setSessions(data);
      });
  }, []);

  return (
    <div className="container">
      <table>
        <thead>
          <tr>
            <td>Move Name</td>
            <td>Outcome</td>
          </tr>
        </thead>
        <tbody>
          {sessions.map((s) => (
            <tr>
              <td>{s.moveName}</td>
              <td>{s.outcome}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <button onClick={() => navigate("/ProfilePage")}>Go Back</button>
    </div>
  );
}

function SummaryPage({ scores }) {
  const navigate = useNavigate();
  function getColor(score) {
    if (score < 40) return "red";
    if (score < 70) return "orange";
    return "green";
  }

  return (
    <div className="container">
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Score</th>
          </tr>
        </thead>
        <tbody>
          {Object.entries(scores)
            .sort((a, b) => a[1] - b[1])
            .map(([group, score]) => (
              <tr key={group}>
                <td style={{ color: getColor(score), fontWeight: "bold" }}>
                  {group}
                </td>
                <td style={{ color: getColor(score), fontWeight: "bold" }}>
                  {score}
                </td>
              </tr>
            ))}
        </tbody>
      </table>
      <button onClick={() => navigate("/ProfilePage")}>Go Back</button>
    </div>
  );
}

function LoginPage({ setUserId, userName, setUserName, setScores }) {
  const [error, setError] = useState("");
  const navigate = useNavigate();

  function login() {
    if (userName === "") {
      setError("Type a username first");
      return;
    }

    setError("");
    fetch(`${API}/login/${userName}`)
      .then((r) => {
        if (!r.ok) {
          return r.text().then((msg) => {
            setError(msg);
          });
        }
        return r.json();
      })
      .then((data) => {
        if (data) {
          setUserId(data.user.id);
          setUserName(data.user.username);
          setScores(data.scores);
          navigate("/ProfilePage");
        }
      })
      .catch((err) => setError(err.message));
  }

  return (
    <div className="container">
      <h2>LOG IN</h2>
      <input value={userName} onChange={(e) => setUserName(e.target.value)} />
      <button onClick={login}>Log In</button>

      {error && (
        <p className="error" color="red">
          {error}
        </p>
      )}
    </div>
  );
}

function ProfilePage({ scores, setScores, userId, userName }) {
  const [moveName, setMoveName] = useState("");
  const [moveId, setMoveId] = useState(0);
  const [moveMG, setMoveMG] = useState("");
  const [moveDiff, setMoveDiff] = useState(0);
  const [completed, setCompleted] = useState(false);
  const [error, setError] = useState("");
  const [showMove, setShowMove] = useState(false); // track if a move was fetched
  const navigate = useNavigate();

  function getBestMove() {
    fetch(`${API}/profile/bestmove/${userId}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(scores),
    })
      .then((r) => {
        if (!r.ok) {
          return r.text().then((msg) => {
            setError(msg);
          });
        }
        return r.json();
      })
      .then((data) => {
        if (data) {
          setMoveId(data.id);
          setMoveName(data.name);
          setMoveMG(data.musclegroup);
          setMoveDiff(data.difficulty);
          setShowMove(true);
        }
      })
      .catch((err) => setError(err.message));
  }

  function submit() {
    fetch(`${API}/profile/outcome`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        userId: userId,
        moveId: moveId,
        completed: completed,
      }),
    })
      .then((r) => {
        if (!r.ok) return r.text().then((err) => setError(err));
        r.text().then((msg) => alert(msg));
        setShowMove(false);
        setCompleted(false);
        const newScores = { ...scores }; // creates a new object reference

        if (completed === true) newScores[moveMG] += 10;
        else newScores[moveMG] -= newScores[moveMG] * 0.08;
        newScores[moveMG] = Math.min(100, Math.max(0, newScores[moveMG])); // clamping
        setScores(newScores);
      })
      .catch((err) => setError(err.message));
  }

  return (
    <div className="container">
      <h1>HELLO {userName}</h1>
      <h1>MAIN PROFILE PAGE</h1>
      <table>
        <thead>
          <tr>
            <th>Muscle Group</th>
            <th>Score</th>
          </tr>
        </thead>
        <tbody>
          {Object.entries(scores).map(([group, score]) => (
            <tr key={group}>
              <td>{group}</td>
              <td>{score}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <button onClick={getBestMove}>See next best move</button>
      {showMove && (
        <div className="container">
          <h2>NEXT BEST MOVE</h2>
          <h3>Move Name: {moveName}</h3>
          <h3>Muscle Group: {moveMG}</h3>
          <h3>Difficulty: {moveDiff}</h3>
          <h3>Complete</h3>
          <input
            type="checkbox"
            checked={completed}
            onChange={(e) => setCompleted(e.target.checked)}
          />
        </div>
      )}

      <button onClick={submit}>Submit</button>
      <br></br>
      <button onClick={() => navigate("/SummaryPage")}> See Sumamry </button>
      <br></br>
      <button onClick={() => navigate("/SessionLogPage")}>
        {" "}
        Session Logs{" "}
      </button>

      {Object.entries(scores).map(
        ([group, score]) =>
          score >= 80 && <h1 key={group}>{group} is on fire today!</h1>,
      )}
      {error && (
        <p className="error" color="red">
          {error}
        </p>
      )}
    </div>
  );
}

export default App;
