// ======================================================
// CAMPUS EVENT SEAT ALLOCATION SYSTEM
// Frontend Interaction
// ======================================================

const TOTAL_SEATS = 20;

let students = [];
let waitingQueue = [];
let cancelledStack = [];

let seats = Array(TOTAL_SEATS).fill(null);


// ======================================================
// INITIAL DATA
// ======================================================

function initializeSeats() {
    seats = Array(TOTAL_SEATS).fill(null);
    updateDashboard();
    displaySeats();
}


// ======================================================
// REGISTER STUDENT
// ======================================================

function registerStudent(id, name, department) {

    id = Number(id);

    // Check duplicate ID
    const existingStudent = students.find(
        student => student.id === id
    );

    const waitingStudent = waitingQueue.find(
        student => student.id === id
    );

    if (existingStudent || waitingStudent) {
        showMessage(
            "Student ID already exists!",
            "error"
        );

        return;
    }


    // Find free seat
    const seatIndex = seats.findIndex(
        seat => seat === null
    );


    // If seat available
    if (seatIndex !== -1) {

        const student = {
            id: id,
            name: name,
            department: department,
            seat: seatIndex + 1
        };

        students.push(student);

        seats[seatIndex] = student;


        showMessage(
            `${name} registered successfully. Seat A-${String(
                seatIndex + 1
            ).padStart(2, "0")} allocated.`,
            "success"
        );

    }

    // If seats are full
    else {

        const student = {
            id: id,
            name: name,
            department: department
        };

        waitingQueue.push(student);


        showMessage(
            `${name} added to Waiting Queue.`,
            "warning"
        );
    }


    updateDashboard();
    displaySeats();
    displayStudents();
    displayQueue();
}


// ======================================================
// CANCEL STUDENT
// ======================================================

function cancelStudent(id) {

    id = Number(id);

    const index = students.findIndex(
        student => student.id === id
    );


    if (index === -1) {

        showMessage(
            "Student not found.",
            "error"
        );

        return;
    }


    const student = students[index];


    // Push into Stack
    cancelledStack.push({
        id: student.id,
        name: student.name,
        seat: student.seat
    });


    // Free seat
    seats[student.seat - 1] = null;


    // Remove from student list
    students.splice(index, 1);


    showMessage(
        `${student.name}'s registration cancelled.`,
        "success"
    );


    // Allocate freed seat to waiting student
    allocateFromQueue(student.seat);


    updateDashboard();
    displaySeats();
    displayStudents();
    displayQueue();
    displayCancelledStack();
}


// ======================================================
// QUEUE → SEAT ALLOCATION
// ======================================================

function allocateFromQueue(seatNumber) {

    if (waitingQueue.length === 0) {
        return;
    }


    // FIFO
    const nextStudent = waitingQueue.shift();


    nextStudent.seat = seatNumber;


    students.push(nextStudent);


    seats[seatNumber - 1] = nextStudent;


    showMessage(
        `${nextStudent.name} moved from Waiting Queue to Seat A-${String(
            seatNumber
        ).padStart(2, "0")}.`,
        "success"
    );
}


// ======================================================
// SEARCH STUDENT
// ======================================================

function searchStudent(id) {

    id = Number(id);


    const student = students.find(
        student => student.id === id
    );


    if (student) {

        return {
            status: "Allocated",
            student: student
        };
    }


    const waiting = waitingQueue.find(
        student => student.id === id
    );


    if (waiting) {

        return {
            status: "Waiting",
            student: waiting
        };
    }


    return null;
}


// ======================================================
// DISPLAY STUDENTS
// ======================================================

function displayStudents() {

    const container =
        document.getElementById("studentList");


    if (!container) {
        return;
    }


    container.innerHTML = "";


    if (students.length === 0) {

        container.innerHTML =
            "<p>No students registered.</p>";

        return;
    }


    students.forEach(student => {

        const card =
            document.createElement("div");

        card.className = "student-card";


        card.innerHTML = `
            <div>
                <strong>${student.name}</strong>
                <p>ID: ${student.id}</p>
                <p>Department: ${student.department}</p>
            </div>

            <div class="seat-badge">
                A-${String(student.seat).padStart(2, "0")}
            </div>
        `;


        container.appendChild(card);
    });
}


// ======================================================
// DISPLAY WAITING QUEUE
// ======================================================

function displayQueue() {

    const container =
        document.getElementById("queueList");


    if (!container) {
        return;
    }


    container.innerHTML = "";


    if (waitingQueue.length === 0) {

        container.innerHTML =
            "<p>Waiting Queue is empty.</p>";

        return;
    }


    waitingQueue.forEach((student, index) => {

        const item =
            document.createElement("div");


        item.className = "queue-item";


        item.innerHTML = `
            <span>
                ${index + 1}. ${student.name}
            </span>

            <span>
                ID: ${student.id}
            </span>
        `;


        container.appendChild(item);
    });
}


// ======================================================
// DISPLAY CANCELLED STACK
// ======================================================

function displayCancelledStack() {

    const container =
        document.getElementById("cancelledList");


    if (!container) {
        return;
    }


    container.innerHTML = "";


    if (cancelledStack.length === 0) {

        container.innerHTML =
            "<p>No cancelled records.</p>";

        return;
    }


    // Stack → Last In First Out
    [...cancelledStack]
        .reverse()
        .forEach((student, index) => {

            const item =
                document.createElement("div");


            item.className = "cancelled-item";


            item.innerHTML = `
                <strong>TOP</strong>
                <p>${student.name}</p>
                <p>ID: ${student.id}</p>
                <p>Previous Seat: A-${String(
                    student.seat
                ).padStart(2, "0")}</p>
            `;


            container.appendChild(item);
        });
}


// ======================================================
// DISPLAY SEAT MAP
// ======================================================

function displaySeats() {

    const container =
        document.getElementById("seatMap");


    if (!container) {
        return;
    }


    container.innerHTML = "";


    seats.forEach((student, index) => {

        const seat =
            document.createElement("div");


        seat.className =
            student
                ? "seat occupied"
                : "seat available";


        seat.innerHTML = `
            <strong>
                A-${String(index + 1).padStart(2, "0")}
            </strong>

            <span>
                ${
                    student
                        ? student.name
                        : "Available"
                }
            </span>
        `;


        container.appendChild(seat);
    });
}


// ======================================================
// DASHBOARD UPDATE
// ======================================================

function updateDashboard() {

    const total =
        document.getElementById("totalSeats");

    const allocated =
        document.getElementById("allocatedSeats");

    const available =
        document.getElementById("availableSeats");

    const waiting =
        document.getElementById("waitingStudents");


    if (total) {
        total.textContent = TOTAL_SEATS;
    }


    if (allocated) {
        allocated.textContent =
            students.length;
    }


    if (available) {
        available.textContent =
            TOTAL_SEATS - students.length;
    }


    if (waiting) {
        waiting.textContent =
            waitingQueue.length;
    }
}


// ======================================================
// MESSAGE SYSTEM
// ======================================================

function showMessage(message, type) {

    const box =
        document.getElementById("message");


    if (!box) {
        alert(message);
        return;
    }


    box.textContent = message;


    box.className =
        `message ${type}`;


    setTimeout(() => {

        box.textContent = "";

        box.className = "message";

    }, 3000);
}


// ======================================================
// REGISTER FORM
// ======================================================

const registerForm =
    document.getElementById("registerForm");


if (registerForm) {

    registerForm.addEventListener(
        "submit",
        function (event) {

            event.preventDefault();


            const id =
                document.getElementById(
                    "studentId"
                ).value;


            const name =
                document.getElementById(
                    "studentName"
                ).value;


            const department =
                document.getElementById(
                    "department"
                ).value;


            if (
                id === "" ||
                name === "" ||
                department === ""
            ) {

                showMessage(
                    "Please fill all fields.",
                    "error"
                );

                return;
            }


            registerStudent(
                id,
                name,
                department
            );


            registerForm.reset();
        }
    );
}


// ======================================================
// CANCEL FORM
// ======================================================

const cancelForm =
    document.getElementById("cancelForm");


if (cancelForm) {

    cancelForm.addEventListener(
        "submit",
        function (event) {

            event.preventDefault();


            const id =
                document.getElementById(
                    "cancelId"
                ).value;


            cancelStudent(id);


            cancelForm.reset();
        }
    );
}


// ======================================================
// SEARCH FORM
// ======================================================

const searchForm =
    document.getElementById("searchForm");


if (searchForm) {

    searchForm.addEventListener(
        "submit",
        function (event) {

            event.preventDefault();


            const id =
                document.getElementById(
                    "searchId"
                ).value;


            const result =
                searchStudent(id);


            if (!result) {

                showMessage(
                    "Student not found.",
                    "error"
                );

                return;
            }


            const student =
                result.student;


            showMessage(
                `${student.name} - ${result.status}`,
                "success"
            );
        }
    );
}


// ======================================================
// INITIALIZE APPLICATION
// ======================================================

initializeSeats();

displayStudents();

displayQueue();

displayCancelledStack();

displaySeats();

updateDashboard();