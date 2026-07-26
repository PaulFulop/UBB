import "./App.css";
import { useState, useEffect } from "react";
import { BrowserRouter, Routes, Route, useNavigate } from "react-router-dom";

const API = "https://localhost:7044";

function App() {
  const [userId, setUserId] = useState(0);
  const [ideas, setIdeas] = useState([]);
  const [selectedIdeaId, setSelectedIdeaId] = useState(0);
  const [clickedIds, setClickedIds] = useState([]);

  return (
    <BrowserRouter>
      <Routes>
        <Route
          path="/"
          element={
            <LoginPage
              userId={setUserId}
              setUserId={setUserId}
              setClickedIds={setClickedIds}
            />
          }
        />
        <Route
          path="/IdeasPage"
          element={
            <IdeasPage
              ideas={ideas}
              setIdeas={setIdeas}
              userId={userId}
              selectedIdeaId={selectedIdeaId}
              setSelectedIdeaId={setSelectedIdeaId}
              clickedIds={clickedIds}
              setClickedIds={setClickedIds}
            />
          }
        />
        <Route
          path="/CommentsPage"
          element={<CommentsPage userId={userId} ideaId={selectedIdeaId} />}
        />
      </Routes>
    </BrowserRouter>
  );
}

function LoginPage({ userId, setUserId, setClickedIds }) {
  const [error, setError] = useState("");
  const [username, setUsername] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    const upvoted = JSON.parse(
      localStorage.getItem(`upvoted_${userId}`) || "[]",
    );
    setClickedIds(upvoted);
  }, [userId]);

  function login() {
    if (username === "") {
      setError("Type a username first");
      return;
    }

    setError("");
    fetch(`${API}/login/${username}`)
      .then((r) => r.json())
      .then((data) => {
        if (data) {
          setUserId(data.id);
          localStorage.setItem("exploredIdeaIds", JSON.stringify([]));
          navigate("/IdeasPage");
        }
      })
      .catch((err) => setError(err.message));

    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
  }

  return (
    <div className="container">
      <h2>LOG IN</h2>
      <input value={username} onChange={(e) => setUsername(e.target.value)} />
      <button onClick={login}>Log In</button>

      {error && (
        <p className="error" color="red">
          {error}
        </p>
      )}
    </div>
  );
}

function IdeasPage({
  ideas,
  setIdeas,
  userId,
  selectedIdeaId,
  setSelectedIdeaId,
  clickedIds,
  setClickedIds,
}) {
  const navigate = useNavigate();
  const [title, setTitle] = useState("");
  const [body, setBody] = useState("");
  const [activeCount, setActiveCount] = useState(0);

  useEffect(() => {
    const fetchIdeas = () => {
      fetch(`${API}/ideas`)
        .then((r) => r.json())
        .then((data) => setIdeas(data))
        .catch((err) => console.error(err));

      fetch(`${API}/login/activecount`)
        .then((r) => r.json())
        .then(setActiveCount);
    };

    fetchIdeas();
    const interval = setInterval(fetchIdeas, 4000);
    return () => clearInterval(interval);
  }, []);

  function expand(ideaId) {
    setSelectedIdeaId(ideaId);

    const explored = JSON.parse(
      localStorage.getItem("exploredIdeaIds") || "[]",
    );
    if (!explored.includes(ideaId)) {
      explored.push(ideaId);
      localStorage.setItem("exploredIdeaIds", JSON.stringify(explored));
    }

    navigate("/CommentsPage");
  }
  function postIdea() {
    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
    fetch(`${API}/ideas/${userId}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        title: title,
        body: body,
      }),
    });
  }

  function logout() {
    localStorage.removeItem("exploredIdeaIds");
    navigate("/");
  }

  function upvote(idea) {
    const num = parseInt(idea.voteCount, 10) + 1;
    const newVotes = num.toString();

    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });

    fetch(`${API}/ideas/${idea.id}`, {
      method: "PATCH",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(newVotes),
    }).then(() => {
      const key = `upvoted_${userId}`;
      const upvoted = JSON.parse(localStorage.getItem(key) || "[]");
      upvoted.push(idea.id);
      localStorage.setItem(key, JSON.stringify(upvoted));
      setClickedIds(upvoted);
    });
  }

  return (
    <div className="container">
      <h3>{activeCount} users active</h3>
      <br />
      <h1>HELLO</h1>
      <br></br>
      <h2>ALL IDEAS</h2>
      <table>
        <thead>
          <tr>
            <td>Title</td>
            <td>Author</td>
            <td>VoteCount</td>
            <td>Number of Comments</td>
          </tr>
        </thead>
        <tbody>
          {ideas.map((i) => (
            <tr key={i.id}>
              <td>{i.title}</td>
              <td>{i.author}</td>
              <td>{i.voteCount}</td>
              <td>{i.numberOfComments}</td>
              <button onClick={() => expand(i.id)}>Expand</button>
              <button
                onClick={() => upvote(i)}
                disabled={clickedIds.includes(i.id)}
              >
                Upvote
              </button>
            </tr>
          ))}
        </tbody>
      </table>

      <h2>ADD A NEW IDEA:</h2>
      <br></br>
      <h3>TITLE: </h3>
      <input value={title} onChange={(e) => setTitle(e.target.value)} />
      <br></br>
      <h3>BODY: </h3>
      <input value={body} onChange={(e) => setBody(e.target.value)} />
      <br></br>
      <button onClick={postIdea}>Post Idea</button>
      <h4>
        You have explored {localStorage.getItem("expandedIdeas")} in this
        session.{" "}
      </h4>
      <button onClick={logout}>Log Out</button>
    </div>
  );
}

function CommentsPage({ userId, ideaId }) {
  const [comments, setComments] = useState([]);
  const [comment, setComment] = useState("");
  const navigate = useNavigate();

  useEffect(() => {
    fetch(`${API}/comments/${ideaId}`)
      .then((r) => r.json())
      .then((data) => setComments(data))
      .catch((err) => console.error(err));
  }, []);

  function postComment() {
    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
    fetch(`${API}/comments/${userId}/${ideaId}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify(comment),
    }).then((data) => {
      setComments([...comments, comment]);
      setComment("");
    });
  }

  return (
    <div className="container">
      <h1>POST A COMMENT</h1>
      <br />
      <input value={comment} onChange={(e) => setComment(e.target.value)} />
      <br />
      <button onClick={postComment}>Post</button>

      <h1>ALL COMMENTS</h1>
      {comments.map((c) => (
        <div>
          <h2>{c}</h2>
          <br />
          <br />
        </div>
      ))}
      <button
        onClick={() => {
          navigate("/IdeasPage");
        }}
      >
        Go Back
      </button>
    </div>
  );
}

export default App;
