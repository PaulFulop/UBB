import "./App.css";
import { useState, useEffect, act } from "react";
import { BrowserRouter, Routes, Route, useNavigate } from "react-router-dom";

const API = "https://localhost:7222";

function App() {
  const [userId, setUserId] = useState(0);
  const [classes, setClasses] = useState([]);
  const [activeBookings, setActiveBookings] = useState([]);
  const [selectedIdeaId, setSelectedIdeaId] = useState(0);
  const [clickedIds, setClickedIds] = useState([]);

  return (
    <BrowserRouter>
      <Routes>
        <Route
          path="/"
          element={<LoginPage userId={userId} setUserId={setUserId} />}
        />
        <Route
          path="/ProfilePage"
          element={
            <ProfilePage
              userId={userId}
              classes={classes}
              setClasses={setClasses}
              activeBookings={activeBookings}
              setActiveBookings={setActiveBookings}
            />
          }
        />
        <Route path="/HistoryPage" element={<HistoryPage userId={userId} />} />
      </Routes>
    </BrowserRouter>
  );
}

function LoginPage({ userId, setUserId }) {
  const [error, setError] = useState("");
  const [username, setUsername] = useState("");
  const navigate = useNavigate();

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
          navigate("/ProfilePage");
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

function ProfilePage({
  userId,
  classes,
  setClasses,
  activeBookings,
  setActiveBookings,
}) {
  const navigate = useNavigate();
  const [message, setMessage] = useState("");
  const [intensityMessage, setIntensityMessage] = useState("");
  const [activeBookingsChanged, setActiveBookingsChanged] = useState(false);
  const [classesChanged, setClassesChanged] = useState(false);
  useEffect(() => {
    fetch(`${API}/classes`)
      .then((r) => r.json())
      .then((data) => {
        setClasses(data);
        setClassesChanged(false);
      })
      .catch((err) => console.error(err));
  }, [classesChanged]);

  useEffect(() => {
    fetch(`${API}/classes/bookings/${userId}`)
      .then((r) => r.json())
      .then((data) => {
        setActiveBookings(data);
        setActiveBookingsChanged(false);
      })
      .catch((err) => console.error(err));
  }, [activeBookingsChanged]);

  function bookClass(userId, classId) {
    fetch(`${API}/classes/${userId}/${classId}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
    })
      .then((r) => r.text())
      .then((msg) => {
        setMessage(msg);
        setClassesChanged(true);
        setActiveBookingsChanged(true);

        // only check intensity AFTER booking completes
        return fetch(`${API}/classes/intensity/${userId}`);
      })
      .then((r) => r.text())
      .then((intensityMsg) => setIntensityMessage(intensityMsg));
  }

  function cancelBooking(userId, classId) {
    fetch(`${API}/classes/cancel/${userId}/${classId}`, {
      method: "POST",
      headers: { "Content-Type": "application/json" },
    })
      .then((r) => r.text())
      .then((msg) => {
        setMessage(msg);
        setActiveBookingsChanged(true);
      });
  }

  return (
    <div className="container">
      <h2>UPCOMING CLASSES</h2>
      <table>
        <thead>
          <tr>
            <td>Class Name</td>
            <td>Instructor Name</td>
            <td>Date</td>
            <td>Remaining Spots</td>
          </tr>
        </thead>
        <tbody>
          {classes.map((c) => (
            <tr key={c.id}>
              <td>{c.className}</td>
              <td>{c.instructorName}</td>
              <td>{c.classDate}</td>
              <td>{c.remainingSpots}</td>
              <button onClick={() => bookClass(userId, c.id)}>
                Book Class
              </button>
            </tr>
          ))}
        </tbody>
      </table>
      <br />
      <h2>ACTIVE BOOKINGS</h2>
      <table>
        <thead>
          <tr>
            <td>Class ID</td>
            <td>Booked At</td>
          </tr>
        </thead>
        <tbody>
          {activeBookings.map((ab) => (
            <tr key={ab.id}>
              <td>{ab.classId}</td>
              <td>{ab.bookedAt}</td>
              <button onClick={() => cancelBooking(userId, ab.classId)}>
                Cancel Booking
              </button>
            </tr>
          ))}
        </tbody>
      </table>

      <button onClick={() => navigate("/HistoryPage")}>Go to history</button>
      <h3>{message}</h3>
      <h3>{intensityMessage}</h3>
    </div>
  );
}
function HistoryPage({ userId }) {
  const [allBookings, setAllBookings] = useState([]);
  const navigate = useNavigate();

  useEffect(() => {
    fetch(`${API}/classes/history/${userId}`)
      .then((r) => r.json())
      .then((data) => setAllBookings(data));
  }, []);

  return (
    <div className="container">
      <h2>ALL BOOKINGS</h2>
      <table>
        <thead>
          <tr>
            <td>Class Name</td>
            <td>Date</td>
            <td>Cancelled</td>
          </tr>
        </thead>
        <tbody>
          {allBookings.map((ab) => (
            <tr key={ab.id}>
              <td>{ab.className}</td>
              <td>{ab.date}</td>
              <td>{ab.status ? "Active" : "Cancelled"}</td>
            </tr>
          ))}
        </tbody>
      </table>
      <br />

      <button onClick={() => navigate("/ProfilePage")}>Go Back</button>
    </div>
  );
}

export default App;
