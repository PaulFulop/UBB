import "./App.css";
import { useState, useEffect } from "react";
import Calendar from "react-calendar";
import "react-calendar/dist/Calendar.css";

const API = "https://localhost:7020";

function App() {
  const [username, setUsername] = useState("");
  const [password, setPassword] = useState("");
  const [userId, setUserId] = useState(0);
  const [loggedIn, setLoggedIn] = useState(false);
  const [error, setError] = useState("");
  const [earliestDate, setEarliestDate] = useState("");
  const [latestDate, setLatestDate] = useState("");
  const [allReservations, setAllReservations] = useState([]);
  const [allRooms, setAllRooms] = useState([]);
  const [numberOfGuests, setNumberOfGuests] = useState(1);
  const [totalGuests, setTotalGuests] = useState(0);

  function login() {
    if (username === "" || password === "") {
      setError("Insert a username or a password!");
      return;
    }

    setError("");
    fetch(`${API}/login`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        username: username,
        password: password,
      }),
    })
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
          setUserId(user.id);
          setLoggedIn(true);
        }
      })
      .catch((err) => setError(err.message));
  }

  useEffect(() => {
    if (!loggedIn) return;

    fetch(`${API}/reservations/${userId}`)
      .then((r) => r.json())
      .then((data) => setAllReservations(data))
      .catch((err) => console.error(err));
  }, [loggedIn, userId]);

  function seeFreeRoomsForInterval() {
    if (!loggedIn) return;

    fetch(`${API}/rooms`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        earliestDate: earliestDate,
        latestDate: latestDate,
      }),
    })
      .then((r) => r.json())
      .then((data) => {
        setAllRooms(data.freeRooms);
        setTotalGuests(data.totalGuests);
      })
      .catch((err) => console.error(err));
  }

  function reserveRoom(roomId, earliestDate, latestDate, numberOfGuests) {
    fetch(`${API}/rooms/reserve`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({
        userId: userId,
        roomId: roomId,
        earliestDate: earliestDate,
        latestDate: latestDate,
        numberOfGuests: numberOfGuests,
      }),
    }).then((r) => {
      if (r.ok) {
        alert("Room reserved");

        fetch(`${API}/reservations/${userId}`)
          .then((r) => r.json())
          .then((data) => setAllReservations(data));
      } else {
        r.text().then((msg) => setError(msg));
      }
    });
  }

  if (!loggedIn) {
    return (
      <div className="container">
        <h2>Enter your name</h2>
        <input value={username} onChange={(e) => setUsername(e.target.value)} />
        <h2>Enter your password</h2>
        <input value={password} onChange={(e) => setPassword(e.target.value)} />
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
      <h2>Insert check-in and check-out:</h2>
      <br></br>
      <Calendar
        onChange={(date) => setEarliestDate(date.toISOString())}
        value={earliestDate ? new Date(earliestDate) : null}
      />
      <Calendar
        onChange={(date) => setLatestDate(date.toISOString())}
        value={latestDate ? new Date(latestDate) : null}
      />
      <input
        value={numberOfGuests}
        onChange={(e) => setNumberOfGuests(e.target.value)}
      />
      <button onClick={seeFreeRoomsForInterval}>See rooms</button>
      <table>
        <thead>
          <tr>
            <th>Room Number</th>
            <th>Capacity</th>
            <th>Base Price</th>
          </tr>
        </thead>
        <tbody>
          {allRooms.map((r) => (
            <tr key={r.id}>
              <td>{r.roomNumber}</td>
              <td>{r.capacity}</td>
              <td>{r.basePrice}</td>
              <td>
                <button
                  onClick={() =>
                    reserveRoom(r.id, earliestDate, latestDate, numberOfGuests)
                  }
                >
                  Reserve
                </button>
              </td>
            </tr>
          ))}
        </tbody>
      </table>
      <p>
        Total guests in hotel for this period: <strong>{totalGuests}</strong>
      </p>

      <h2>My Reservations</h2>
      <table>
        <thead>
          <tr>
            <th>Room ID</th>
            <th>Check In</th>
            <th>Check Out</th>
            <th>Guests</th>
            <th>Total Price</th>
          </tr>
        </thead>
        <tbody>
          {allReservations.map((res) => (
            <tr key={res.id}>
              <td>{res.roomId}</td>
              <td>{res.checkInDate}</td>
              <td>{res.checkOutDate}</td>
              <td>{res.numberOfGuests}</td>
              <td>{res.totalPrice}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <p>{error}</p>
    </div>
  );
}

export default App;
