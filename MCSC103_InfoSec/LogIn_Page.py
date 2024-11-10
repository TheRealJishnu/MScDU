import tkinter as tk
from tkinter import messagebox
import hashlib
import os

# Hashing function
def hash_password(password):
    return hashlib.sha256(password.encode()).hexdigest()

# Function to register a new user
def register_user():
    username = username_entry.get()
    password = password_entry.get()

    if not username or not password:
        messagebox.showwarning("Input Error", "Please fill out both fields.")
        return

    hashed_password = hash_password(password)


    # Check if username exists
    with open("users.txt", "r") as file:
        users = file.readlines()
        for user in users:
            existing, _ = user.strip().split(":")
            if username == existing:
                messagebox.showerror("Registration Error", "Username already exists.")
                return

    # Store the new user 
    with open("users.txt", "a") as file:
        file.write(f"{username}:{hashed_password}\n")
    messagebox.showinfo("Registration Success", "User registered successfully!")


def open_question_window():
    question_window = tk.Toplevel(root)
    question_window.title("Two Factor Authentication")
    question_window.geometry("300x200")

    # Question 1
    tk.Label(question_window, text="Do you pinky promise this is your account?").pack(pady=5)
    question1_var = tk.StringVar(value="No")  # Default to "No"
    tk.Radiobutton(question_window, text="Yes", variable=question1_var, value="Yes").pack()
    tk.Radiobutton(question_window, text="No", variable=question1_var, value="No").pack()

    # Question 2
    tk.Label(question_window, text="Maa kasam this is your account?").pack(pady=5)
    question2_var = tk.StringVar(value="No")  # Default to "No"
    tk.Radiobutton(question_window, text="Yes", variable=question2_var, value="Yes").pack()
    tk.Radiobutton(question_window, text="No", variable=question2_var, value="No").pack()


    def check_answers():
        if question1_var.get() == "Yes" and question2_var.get() == "Yes":
            messagebox.showinfo("Login Success", "Successfully logged into Jishnu's assignment!")
        else:
            messagebox.showwarning("Access Denied", "Both answers must be 'Yes' to log in.")
            question_window.destroy()  # Close the question window


    tk.Button(question_window, text="Submit", command=check_answers).pack(pady=10)


def login_user():
    username = username_entry.get()
    password = password_entry.get()

    if not username or not password:
        messagebox.showwarning("Input Error", "Please fill out both fields.")
        return

    hashed_password = hash_password(password)


    with open("users.txt", "r") as file:
        users = file.readlines()
        for user in users:
            stored_username, stored_password = user.strip().split(":")
            if username == stored_username and hashed_password == stored_password:
                messagebox.showinfo("Password Matched", "Click ok for 2 Factor Authentication")
                open_question_window()  # Open the question window after login
                return

    messagebox.showerror("Login Failed", "Incorrect username or password.")


if 'users.txt' not in os.listdir(os.path.dirname(os.path.realpath(__file__))):
    newf = os.path.join(os.path.dirname(os.path.realpath(__file__)), "users.txt")
    f = open(newf, 'w')
    f.close()


# GUI
root = tk.Tk()
root.title("Login System")
root.geometry("600x400")


tk.Label(root, text="Username:").pack(pady=5)
username_entry = tk.Entry(root)
username_entry.pack(pady=5)

tk.Label(root, text="Password:").pack(pady=5)
password_entry = tk.Entry(root, show="*")
password_entry.pack(pady=5)


tk.Button(root, text="Register", command=register_user).pack(pady=5)
tk.Button(root, text="Login", command=login_user).pack(pady=5)


root.mainloop()
