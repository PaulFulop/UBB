import "./App.css";
import { useState, useEffect } from "react";
import { BrowserRouter, Routes, Route, useNavigate } from "react-router-dom";

const API = "https://localhost:7166";

function App() {
  const [userId, setUserId] = useState(0);
  const [itemId, setItemId] = useState(0);
  const [items, setItems] = useState([]);
  const [username, setUsername] = useState("");
  const [itemName, setItemName] = useState("");
  return (
    <BrowserRouter>
      <Routes>
        <Route
          path="/"
          element={
            <LoginPage
              username={username}
              setUsername={setUsername}
              userId={userId}
              setUserId={setUserId}
            />
          }
        />
        <Route
          path="/BoardPage"
          element={
            <BoardPage
              userId={userId}
              items={items}
              setItems={setItems}
              setItemId={setItemId}
              username={username}
              setItemName={setItemName}
            />
          }
        />
        <Route
          path="/HistoryPage"
          element={
            <HistoryPage userId={userId} itemId={itemId} itemName={itemName} />
          }
        />
      </Routes>
    </BrowserRouter>
  );
}

function LoginPage({ username, setUsername, userId, setUserId }) {
  const [error, setError] = useState("");
  const navigate = useNavigate();

  function login() {
    if (username === "") {
      setError("Type a username first");
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
      .then((data) => {
        if (data) {
          setUserId(data.id);
          fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
          navigate("/BoardPage");
        }
      })
      .catch((err) => setError(err.message));
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

function BoardPage({
  username,
  userId,
  items,
  setItems,
  setItemId,
  setItemName,
}) {
  const navigate = useNavigate();
  const [title, setTitle] = useState("");
  const [desc, setDesc] = useState("");
  const [price, setPrice] = useState("");
  const [activeCount, setActiveCount] = useState(1);
  const [msg, setMsg] = useState("");

  useEffect(() => {
    const fetchItems = () => {
      fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
      fetch(`${API}/board/items`)
        .then((r) => r.json())
        .then((data) => setItems(data));

      fetch(`${API}/login/activecount`)
        .then((r) => r.json())
        .then((data) => setActiveCount(parseInt(data)));
    };

    fetchItems();
    const interval = setInterval(fetchItems, 10000);
    return () => clearInterval(interval);
  }, []);

  function addItem() {
    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
    fetch(`${API}/board/items/${userId}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        title: title,
        description: desc,
        startingPrice: parseInt(price),
      }),
    })
      .then((r) => r.text())
      .then((message) => setMsg(message));
  }

  function deleteItem(itemId) {
    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
    fetch(`${API}/board/items/${userId}/${itemId}`, {
      method: "DELETE",
      headers: { "Content-Type": "application/json" },
    })
      .then((r) => r.text())
      .then((message) => setMsg(message));
  }

  return (
    <div className="container">
      <h2>
        {activeCount} users have ineracted with the board in the last 60 seconds
      </h2>
      <h1>HELLO {username} </h1>
      <br />
      <table>
        <thead>
          <tr>
            <td>Title</td>
            <td>Seller</td>
            <td>Current Price</td>
            <td>Bids</td>
          </tr>
        </thead>
        <tbody>
          {items.map((i) => (
            <tr key={i.id}>
              <td>{i.title}</td>
              <td>{i.seller}</td>
              <td>{i.currentPrice}</td>
              <td>{i.numOfBids}</td>
              <button
                onClick={() => {
                  setItemId(i.id);
                  setItemName(i.title);
                  navigate("/HistoryPage");
                }}
              >
                Expand
              </button>
              <button onClick={() => deleteItem(i.id)}>Delete</button>
            </tr>
          ))}
        </tbody>
      </table>
      <br />
      <h1>ADD ITEM:</h1>
      <h2>Title:</h2>
      <input value={title} onChange={(e) => setTitle(e.target.value)} />
      <br />
      <h2>Description:</h2>
      <input value={desc} onChange={(e) => setDesc(e.target.value)} />
      <br />
      <h2>Price: </h2>
      <input value={price} onChange={(e) => setPrice(e.target.value)} />
      <button onClick={addItem}>Add</button>
      <h2>{msg}</h2>
    </div>
  );
}

function HistoryPage({ userId, itemId, itemName }) {
  const navigate = useNavigate();
  const [bids, setBids] = useState([]);
  const [amount, setAmount] = useState("");
  const [msg, setMsg] = useState("");
  const [added, setAdded] = useState(false);

  useEffect(() => {
    fetch(`${API}/board/items/history/${itemId}`)
      .then((r) => r.json())
      .then((data) => {
        setBids(data);
        setAdded(false);
      });
  }, [added]);

  function addBid() {
    fetch(`${API}/login/heartbeat/${userId}`, { method: "POST" });
    const amountInt = parseInt(amount);
    fetch(`${API}/board/items/history/place/${userId}/${itemId}/${amountInt}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
    })
      .then((r) => r.text())
      .then((message) => {
        setMsg(message);
        setAdded(true);
      });
  }

  return (
    <div className="container">
      <table>
        <thead>
          <tr>
            <td>Item</td>
            <td>User</td>
            <td>Amount</td>
            <td>Placed At</td>
          </tr>
        </thead>
        <tbody>
          {bids.map((b) => (
            <tr key={b.id}>
              <td>{b.itemName}</td>
              <td>{b.userName}</td>
              <td>{b.amount}</td>
              <td>{b.placedAt}</td>
            </tr>
          ))}
        </tbody>
      </table>

      <h1>ADD BID TO {itemName}:</h1>
      <input value={amount} onChange={(e) => setAmount(e.target.value)} />
      <button onClick={addBid}>Add</button>

      <button onClick={() => navigate("/BoardPage")}>Go Back</button>
      <h2>{msg}</h2>
    </div>
  );
}

export default App;
