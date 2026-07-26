import "./App.css";
import { useState, useEffect } from "react";

const API = "https://localhost:7132";

function App() {
  const [username, setUsername] = useState("");
  const [userId, setUserId] = useState("");
  const [loggedIn, setLoggedIn] = useState(false);
  const [totalPriceMessage, setTotalPriceMessage] = useState("");
  const [allProducts, setAllProducts] = useState([]);
  const [chosenProducts, setChosenProducts] = useState([]);
  const [error, setError] = useState("");

  function login() {
    if (username === "") {
      setError("Type a username first please");
      return;
    }

    setError("");
    fetch(`${API}/login/${username}`)
      .then((r) => r.json())
      .then((data) => {
        setUserId(data.id);
        setLoggedIn(true);
      })
      .catch((err) => setError(err.message));
  }

  function confirmOrder() {
    fetch(`${API}/orders`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        userId: userId,
        products: chosenProducts,
      }),
    })
      .then((r) => r.json())
      .then((data) => {
        setTotalPriceMessage("Total price: " + data.totalPrice);
        setChosenProducts([]);
        alert("Order confirmed!");
      })
      .catch((err) => setError(err.message));
  }

  useEffect(() => {
    if (!loggedIn) return;

    fetch(`${API}/products`)
      .then((r) => r.json())
      .then((data) => setAllProducts(data))
      .catch((err) => console.error(err));
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

  return (
    <div className="container">
      <h2> Hello {username}! </h2>
      <br></br>
      <h3>All products</h3>
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Price</th>
          </tr>
        </thead>
        <tbody>
          {allProducts.map((p) => (
            <tr key={p.id}>
              <td>{p.name}</td>
              <td>{p.price}</td>
              <td>
                <button
                  onClick={() => setChosenProducts((prev) => [...prev, p])}
                >
                  Add Product
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>

      <h3>Chosen products</h3>
      <table>
        <thead>
          <tr>
            <th>Name</th>
            <th>Price</th>
          </tr>
        </thead>
        <tbody>
          {chosenProducts.map((p) => (
            <tr key={p.id}>
              <td>{p.name}</td>
              <td>{p.price}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <button onClick={confirmOrder}>Confirm Order</button>
      <p>{totalPriceMessage}</p>
      <p>{error}</p>
    </div>
  );
}

export default App;
