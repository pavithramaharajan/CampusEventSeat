import streamlit as st


# ============================================================
# PAGE CONFIG
# ============================================================

st.set_page_config(
    page_title="CampusFlow",
    page_icon="🎓",
    layout="wide",
    initial_sidebar_state="collapsed"
)


# ============================================================
# SESSION STATE
# ============================================================

if "page" not in st.session_state:
    st.session_state.page = "landing"

if "logged_in" not in st.session_state:
    st.session_state.logged_in = False

if "user_name" not in st.session_state:
    st.session_state.user_name = ""


# ============================================================
# CSS
# ============================================================

st.markdown(
    """
    <style>

    .stApp {
        background-color: #07111f;
    }

    .main .block-container {
        max-width: 1200px;
        padding-top: 35px;
        padding-bottom: 40px;
    }

    h1, h2, h3 {
        color: white !important;
    }

    p, label {
        color: #cbd5e1 !important;
    }

    /* Buttons */

    .stButton > button {
        width: 100%;
        min-height: 48px;
        border-radius: 12px;
        border: 1px solid #334155;
        background-color: #111c2e;
        color: white;
        font-weight: 700;
    }

    .stButton > button:hover {
        border-color: #60a5fa;
        color: white;
        background-color: #172554;
    }

    /* Inputs */

    .stTextInput input,
    .stNumberInput input {
        background-color: #0f1b2d;
        color: white;
        border: 1px solid #334155;
        border-radius: 10px;
    }

    /* Select */

    .stSelectbox div[data-baseweb="select"] > div {
        background-color: #0f1b2d;
        color: white;
        border-radius: 10px;
        border: 1px solid #334155;
    }

    /* Metric */

    [data-testid="stMetric"] {
        background-color: #0f1b2d;
        border: 1px solid #26364d;
        padding: 18px;
        border-radius: 16px;
    }

    [data-testid="stMetricLabel"] {
        color: #94a3b8 !important;
    }

    [data-testid="stMetricValue"] {
        color: white !important;
    }

    /* Sidebar */

    section[data-testid="stSidebar"] {
        background-color: #081426;
    }

    /* Divider */

    hr {
        border-color: #243449;
    }

    </style>
    """,
    unsafe_allow_html=True
)


# ============================================================
# DATA
# ============================================================

TOTAL_SEATS = 20

students = [
    {
        "id": 101,
        "name": "Arun Kumar",
        "department": "AI&DS",
        "seat": 1
    },
    {
        "id": 102,
        "name": "Priya S",
        "department": "CSE",
        "seat": 2
    },
    {
        "id": 103,
        "name": "Kavin R",
        "department": "IT",
        "seat": 3
    },
    {
        "id": 104,
        "name": "Divya M",
        "department": "AI&DS",
        "seat": 4
    },
    {
        "id": 105,
        "name": "Rahul P",
        "department": "ECE",
        "seat": 5
    },
    {
        "id": 106,
        "name": "Meena K",
        "department": "CSE",
        "seat": 6
    },
    {
        "id": 107,
        "name": "Vishnu",
        "department": "IT",
        "seat": 7
    },
    {
        "id": 108,
        "name": "Harini",
        "department": "AI&DS",
        "seat": 8
    }
]

waiting = [
    {
        "id": 109,
        "name": "Sanjay"
    },
    {
        "id": 110,
        "name": "Keerthana"
    },
    {
        "id": 111,
        "name": "Ajay"
    }
]

cancelled = [
    {
        "id": 95,
        "name": "Naveen",
        "seat": 12
    },
    {
        "id": 92,
        "name": "Deepa",
        "seat": 9
    }
]


# ============================================================
# LANDING PAGE
# ============================================================

def landing_page():

    st.caption("🎓  CAMPUSFLOW  •  SMART EVENT MANAGEMENT")

    st.title("Smarter Events.")
    st.header("Simpler Seat Allocation.")

    st.write(
        "A modern campus event management application for "
        "student registration, seat allocation, waiting-list "
        "management and cancellation tracking."
    )

    st.write("")

    col1, col2, col3 = st.columns([1, 1, 1])

    with col1:
        st.metric(
            "SEATS",
            "20"
        )

    with col2:
        st.metric(
            "ALLOCATED",
            "8"
        )

    with col3:
        st.metric(
            "WAITING",
            "3"
        )

    st.write("")
    st.write("")

    st.subheader("Built Around Data Structures")

    c1, c2, c3, c4 = st.columns(4)

    with c1:
        st.info(
            "🔗 **Linked List**\n\n"
            "Dynamic student registration."
        )

    with c2:
        st.info(
            "⏳ **Queue**\n\n"
            "FIFO waiting-list management."
        )

    with c3:
        st.info(
            "📚 **Stack**\n\n"
            "LIFO cancellation history."
        )

    with c4:
        st.info(
            "🪑 **Array**\n\n"
            "Fast seat availability tracking."
        )

    st.write("")
    st.write("")

    st.subheader("Get Started")

    b1, b2, b3 = st.columns([1, 2, 1])

    with b2:

        login_button, signup_button = st.columns(2)

        with login_button:

            if st.button(
                "🔐 Login",
                use_container_width=True
            ):
                st.session_state.page = "login"
                st.rerun()

        with signup_button:

            if st.button(
                "✨ Create Account",
                use_container_width=True
            ):
                st.session_state.page = "signup"
                st.rerun()

    st.write("")
    st.caption(
        "Data Structures Using C • Campus Event Seat Allocation System"
    )


# ============================================================
# LOGIN PAGE
# ============================================================

def login_page():

    st.caption("🎓 CAMPUSFLOW")

    st.title("Welcome Back")

    st.write(
        "Sign in to access your event management workspace."
    )

    st.write("")

    col1, col2, col3 = st.columns([1, 2, 1])

    with col2:

        email = st.text_input(
            "Email Address",
            placeholder="student@example.com"
        )

        password = st.text_input(
            "Password",
            type="password",
            placeholder="Enter your password"
        )

        st.write("")

        if st.button(
            "Sign In →",
            use_container_width=True
        ):

            if email.strip() == "" or password.strip() == "":
                st.error(
                    "Please enter both email and password."
                )

            else:

                st.session_state.logged_in = True
                st.session_state.user_name = email.split("@")[0]
                st.session_state.page = "dashboard"

                st.success(
                    "Login successful!"
                )

                st.rerun()

        st.write("")

        if st.button(
            "← Back to Home",
            use_container_width=True
        ):
            st.session_state.page = "landing"
            st.rerun()

        st.write("")

        st.info(
            "Demo Login: enter any email and password."
        )


# ============================================================
# SIGN UP PAGE
# ============================================================

def signup_page():

    st.caption("🎓 CAMPUSFLOW")

    st.title("Create Your Account")

    st.write(
        "Create an account to manage your campus events."
    )

    st.write("")

    col1, col2, col3 = st.columns([1, 2, 1])

    with col2:

        name = st.text_input(
            "Full Name",
            placeholder="Enter your full name"
        )

        email = st.text_input(
            "Email Address",
            placeholder="student@example.com"
        )

        password = st.text_input(
            "Password",
            type="password",
            placeholder="Create a password"
        )

        confirm_password = st.text_input(
            "Confirm Password",
            type="password",
            placeholder="Confirm your password"
        )

        st.write("")

        if st.button(
            "Create Account →",
            use_container_width=True
        ):

            if (
                name.strip() == ""
                or email.strip() == ""
                or password.strip() == ""
            ):

                st.error(
                    "Please complete all fields."
                )

            elif password != confirm_password:

                st.error(
                    "Passwords do not match."
                )

            else:

                st.success(
                    "Account created successfully!"
                )

                st.session_state.page = "login"

                st.rerun()

        st.write("")

        if st.button(
            "← Back to Home",
            use_container_width=True
        ):

            st.session_state.page = "landing"
            st.rerun()


# ============================================================
# DASHBOARD
# ============================================================

def dashboard_page():

    with st.sidebar:

        st.title("🎓 CampusFlow")

        st.caption("Event Seat Management")

        st.divider()

        selected_page = st.radio(
            "Navigation",
            [
                "Overview",
                "Register Student",
                "Search Student",
                "Seat Map",
                "Waiting Queue",
                "Cancellation History"
            ]
        )

        st.divider()

        st.success("● System Online")

        st.caption("Data Structure Engine: C")

        st.caption(
            "Logged in as: "
            + st.session_state.user_name
        )

        if st.button(
            "Logout",
            use_container_width=True
        ):

            st.session_state.logged_in = False
            st.session_state.page = "landing"
            st.rerun()


    st.title("Campus Event Seat Allocation")

    st.write(
        "Manage student registration, seats and waiting lists "
        "from one workspace."
    )

    st.write("")

    allocated = len(students)
    available = TOTAL_SEATS - allocated

    m1, m2, m3, m4 = st.columns(4)

    with m1:
        st.metric(
            "TOTAL SEATS",
            TOTAL_SEATS
        )

    with m2:
        st.metric(
            "ALLOCATED",
            allocated
        )

    with m3:
        st.metric(
            "AVAILABLE",
            available
        )

    with m4:
        st.metric(
            "WAITING",
            len(waiting)
        )


    st.divider()


    # ========================================================
    # OVERVIEW
    # ========================================================

    if selected_page == "Overview":

        st.subheader("Event Overview")

        left, right = st.columns(2)

        with left:

            st.write("### 📊 Seat Utilization")

            utilization = allocated / TOTAL_SEATS

            st.progress(
                utilization
            )

            st.write(
                f"**{allocated} / {TOTAL_SEATS} seats allocated**"
            )

            st.caption(
                f"{utilization * 100:.0f}% capacity utilized."
            )


        with right:

            st.write("### 🧠 Data Structure Engine")

            st.info(
                "🔗 Linked List — Registered students"
            )

            st.info(
                "⏳ Queue — Waiting students"
            )

            st.info(
                "📚 Stack — Cancellation records"
            )

            st.info(
                "🪑 Array — Seat tracking"
            )


    # ========================================================
    # REGISTER
    # ========================================================

    elif selected_page == "Register Student":

        st.subheader("📝 Register Student")

        with st.form("register_form"):

            student_id = st.number_input(
                "Student ID",
                min_value=1,
                step=1
            )

            name = st.text_input(
                "Student Name"
            )

            department = st.selectbox(
                "Department",
                [
                    "AI&DS",
                    "CSE",
                    "IT",
                    "ECE",
                    "EEE",
                    "MECH"
                ]
            )

            event = st.selectbox(
                "Event",
                [
                    "TechFest 2026",
                    "AI Innovation Challenge",
                    "Coding Arena",
                    "Project Expo"
                ]
            )

            submitted = st.form_submit_button(
                "Allocate Seat →",
                use_container_width=True
            )

        if submitted:

            if name.strip() == "":
                st.error(
                    "Please enter student name."
                )

            else:
                st.success(
                    f"{name} registered successfully!"
                )

                st.info(
                    "The C Data Structure engine will "
                    "allocate the next available seat."
                )


    # ========================================================
    # SEARCH
    # ========================================================

    elif selected_page == "Search Student":

        st.subheader("🔎 Search Student")

        search_id = st.number_input(
            "Enter Student ID",
            min_value=1,
            step=1
        )

        if st.button(
            "Search Student",
            use_container_width=True
        ):

            found = None

            for student in students:

                if student["id"] == search_id:
                    found = student
                    break

            if found:

                st.success(
                    "Student found!"
                )

                a, b, c, d = st.columns(4)

                with a:
                    st.metric(
                        "ID",
                        found["id"]
                    )

                with b:
                    st.metric(
                        "Name",
                        found["name"]
                    )

                with c:
                    st.metric(
                        "Department",
                        found["department"]
                    )

                with d:
                    st.metric(
                        "Seat",
                        f"A-{found['seat']:02d}"
                    )

            else:

                st.error(
                    "Student not found."
                )


    # ========================================================
    # SEAT MAP
    # ========================================================

    elif selected_page == "Seat Map":

        st.subheader("🪑 Live Seat Map")

        occupied = {}

        for student in students:
            occupied[student["seat"]] = student["name"]


        for row in range(4):

            columns = st.columns(5)

            for index in range(5):

                seat_number = row * 5 + index + 1

                with columns[index]:

                    if seat_number in occupied:

                        st.error(
                            f"🔴 A-{seat_number:02d}\n\n"
                            f"{occupied[seat_number]}"
                        )

                    else:

                        st.success(
                            f"🟢 A-{seat_number:02d}\n\n"
                            "AVAILABLE"
                        )


    # ========================================================
    # WAITING QUEUE
    # ========================================================

    elif selected_page == "Waiting Queue":

        st.subheader("⏳ Waiting Queue")

        st.warning(
            "FIFO — First In, First Out"
        )

        for position, student in enumerate(
            waiting,
            start=1
        ):

            st.info(
                f"**#{position}**  "
                f"{student['name']}  |  "
                f"Student ID: {student['id']}"
            )


    # ========================================================
    # CANCELLATION STACK
    # ========================================================

    elif selected_page == "Cancellation History":

        st.subheader("📚 Cancellation History")

        st.warning(
            "LIFO — Last In, First Out"
        )

        for student in reversed(cancelled):

            st.info(
                f"**TOP → {student['name']}**  |  "
                f"ID: {student['id']}  |  "
                f"Previous Seat: A-{student['seat']:02d}"
            )


# ============================================================
# ROUTER
# ============================================================

if st.session_state.logged_in:

    dashboard_page()

elif st.session_state.page == "login":

    login_page()

elif st.session_state.page == "signup":

    signup_page()

else:

    landing_page()