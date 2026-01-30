import json
import random
import tkinter as tk
from tkinter import ttk, messagebox
import os


class RoundedFrame(tk.Canvas):
    """A frame with rounded corners"""
    def __init__(self, parent, radius=10, bg='#1a1a1a', border_color='#2f2f2f', border_width=0, **kwargs):
        super().__init__(parent, bg=bg, highlightthickness=0, **kwargs)
        self.radius = radius
        self.bg_color = bg
        self.border_color = border_color
        self.border_width = border_width
        self.inner_frame = tk.Frame(self, bg=bg)
        self.bind('<Configure>', self._draw_rounded_rect)
    
    def _draw_rounded_rect(self, event=None):
        self.delete("rounded_rect")
        w = self.winfo_width()
        h = self.winfo_height()
        r = self.radius
        
        if self.border_width > 0:
            self.create_rounded_rectangle(0, 0, w, h, r, fill=self.border_color, outline='', tags="rounded_rect")
            bw = self.border_width
            self.create_rounded_rectangle(bw, bw, w-bw, h-bw, r-bw, fill=self.bg_color, outline='', tags="rounded_rect")
        else:
            self.create_rounded_rectangle(0, 0, w, h, r, fill=self.bg_color, outline='', tags="rounded_rect")
        
        self.create_window(w/2, h/2, window=self.inner_frame, tags="rounded_rect")
    
    def create_rounded_rectangle(self, x1, y1, x2, y2, radius, **kwargs):
        points = [x1+radius, y1, x1+radius, y1, x2-radius, y1, x2-radius, y1, x2, y1,
                  x2, y1+radius, x2, y1+radius, x2, y2-radius, x2, y2-radius, x2, y2,
                  x2-radius, y2, x2-radius, y2, x1+radius, y2, x1+radius, y2, x1, y2,
                  x1, y2-radius, x1, y2-radius, x1, y1+radius, x1, y1+radius, x1, y1]
        return self.create_polygon(points, smooth=True, **kwargs)


class QuizApp:
    BG_DARK = "#0d0d0d"
    BG_CARD = "#1a1a1a"
    BG_HOVER = "#2a2a2a"
    BTN_HOVER = "#333333"
    BORDER = "#2f2f2f"
    ACCENT = "#6b9fff"
    ACCENT_DIM = "#4a6fa5"
    SUCCESS = "#4caf50"
    SUCCESS_DARK = "#3d8b40"
    ERROR = "#e57373"
    ERROR_DARK = "#c62828"
    WARNING = "#ffb74d"
    TEXT_PRIMARY = "#e8e8e8"
    TEXT_SECONDARY = "#a0a0a0"
    TEXT_MUTED = "#606060"
    
    def __init__(self, root):
        self.root = root
        self.root.title("Network Quiz")
        
        window_width, window_height = 900, 900
        screen_width = root.winfo_screenwidth()
        screen_height = root.winfo_screenheight()
        x = (screen_width - window_width) // 2
        y = (screen_height - window_height) // 2
        
        self.root.geometry(f"{window_width}x{window_height}+{x}+{y}")
        self.root.resizable(False, False)
        self.root.configure(bg=self.BG_DARK)
        self.setup_styles()
        
        with open('questions.json', 'r', encoding='utf-8-sig') as f:
            self.questions = json.load(f)
        
        # Load or initialize performance data
        self.performance_file = 'performance_data.json'
        self.performance_data = self.load_performance_data()
        
        self.current_question_index = 0
        self.score = 0
        self.wrong_answers = []
        self.indexes_of_questions = []
        self.nr_of_questions = 0
        self.current_q = None
        self.current_q_id = None
        self.pending_callback = None
        self.game_mode = 'random'  # 'random' or 'adaptive'
        self.selected_answers = set()  # Track selected answers for multi-select questions
        self.answer_buttons = {}  # Store answer button references for updating UI
        
        self.show_welcome_screen()
    
    def setup_styles(self):
        style = ttk.Style()
        style.theme_use('clam')
        style.configure("Vertical.TScrollbar", background=self.BG_CARD, troughcolor=self.BG_DARK, borderwidth=0, arrowsize=12)
    
    def load_performance_data(self):
        """Load performance data from file or initialize new data structure"""
        if os.path.exists(self.performance_file):
            try:
                with open(self.performance_file, 'r', encoding='utf-8') as f:
                    return json.load(f)
            except:
                pass
        
        # Initialize performance data for all questions
        performance = {}
        for i in range(len(self.questions)):
            performance[str(i)] = {
                'timesAnswered': 0,
                'timesCorrect': 0,
                'timesIncorrect': 0
            }
        return performance
    
    def save_performance_data(self):
        """Save performance data to file"""
        with open(self.performance_file, 'w', encoding='utf-8') as f:
            json.dump(self.performance_data, f, indent=2)
    
    def reset_performance_data(self):
        """Reset all performance data to zero"""
        result = messagebox.askyesno(
            "Reset Performance Data",
            "Are you sure you want to reset all performance tracking?\n\nThis will clear all your progress and cannot be undone."
        )
        if result:
            self.performance_data = self.load_performance_data()
            # Reset all values to zero
            for key in self.performance_data:
                self.performance_data[key] = {
                    'timesAnswered': 0,
                    'timesCorrect': 0,
                    'timesIncorrect': 0
                }
            self.save_performance_data()
            messagebox.showinfo("Success", "Performance data has been reset!")
    
    def calculate_priority_score(self, question_id):
        """Calculate priority score for a question (higher = more priority)
        
        Priority ranking:
        1. Questions with most incorrect answers (highest priority)
        2. Questions with mixed results (medium priority)
        3. Questions mostly correct (lowest priority)
        """
        data = self.performance_data.get(str(question_id), {'timesIncorrect': 0, 'timesCorrect': 0, 'timesAnswered': 0})
        incorrect = data['timesIncorrect']
        correct = data['timesCorrect']
        answered = data['timesAnswered']
        
        if answered == 0:
            return 0
        
        # Calculate incorrect ratio
        incorrect_ratio = incorrect / answered
        
        # Priority formula - heavily weights incorrect answers
        # Base score: incorrect count weighted heavily (x20)
        # Ratio bonus: rewards consistently incorrect questions (x15)
        # Penalty: reduce priority for questions that are mostly correct
        base_score = incorrect * 20
        ratio_bonus = incorrect_ratio * 15
        correct_penalty = correct * -2  # Slightly reduce priority if many correct
        
        priority = base_score + ratio_bonus + correct_penalty
        
        # Ensure priority is never negative
        return max(0, priority)
    
    def update_performance(self, question_id, is_correct):
        """Update performance metrics for a question"""
        q_id = str(question_id)
        if q_id not in self.performance_data:
            self.performance_data[q_id] = {
                'timesAnswered': 0,
                'timesCorrect': 0,
                'timesIncorrect': 0
            }
        
        self.performance_data[q_id]['timesAnswered'] += 1
        if is_correct:
            self.performance_data[q_id]['timesCorrect'] += 1
        else:
            self.performance_data[q_id]['timesIncorrect'] += 1
        
        self.save_performance_data()
    
    def clear_window(self):
        if self.pending_callback:
            self.root.after_cancel(self.pending_callback)
            self.pending_callback = None
        for widget in self.root.winfo_children():
            widget.destroy()
    
    def show_welcome_screen(self):
        self.clear_window()
        container = tk.Frame(self.root, bg=self.BG_DARK)
        container.place(relx=0.5, rely=0.5, anchor='center')
        
        tk.Label(container, text="🌐", font=('Segoe UI', 48), bg=self.BG_DARK, fg=self.ACCENT_DIM).pack(pady=(0, 8))
        tk.Label(container, text="Network Quiz", font=('Segoe UI', 32, 'bold'), bg=self.BG_DARK, fg=self.TEXT_PRIMARY).pack()
        tk.Label(container, text="Test your networking knowledge", font=('Segoe UI', 12), bg=self.BG_DARK, fg=self.TEXT_MUTED).pack(pady=(8, 20))
        
        card = RoundedFrame(container, radius=12, bg=self.BG_CARD, border_color=self.BORDER, border_width=1)
        card.pack(pady=8)
        card.configure(width=280, height=50)
        tk.Label(card.inner_frame, text=f"{len(self.questions)} questions available", font=('Segoe UI', 11), bg=self.BG_CARD, fg=self.TEXT_SECONDARY).pack()
        
        # Mode selection
        tk.Label(container, text="Select Mode", font=('Segoe UI', 12, 'bold'), bg=self.BG_DARK, fg=self.TEXT_PRIMARY).pack(pady=(18, 8))
        
        mode_frame = tk.Frame(container, bg=self.BG_DARK)
        mode_frame.pack(pady=3)
        
        # Random Mode Button
        self.create_mode_button(mode_frame, "🎲 Random Mode", "random", 
                               "Questions selected randomly", side='left', padx=(0, 8))
        
        # Adaptive Mode Button
        self.create_mode_button(mode_frame, "🎯 Review Mode", "adaptive", 
                               "Focus on weak areas", side='left', padx=(8, 0))
        
        input_frame = tk.Frame(container, bg=self.BG_DARK)
        input_frame.pack(pady=18)
        tk.Label(input_frame, text="Questions:", font=('Segoe UI', 11), bg=self.BG_DARK, fg=self.TEXT_MUTED).pack(side='left', padx=(0, 12))
        
        entry_canvas = RoundedFrame(input_frame, radius=8, bg=self.BG_CARD, border_color=self.BORDER, border_width=1)
        entry_canvas.pack(side='left')
        entry_canvas.configure(width=80, height=44)
        self.count_entry = tk.Entry(entry_canvas.inner_frame, font=('Segoe UI', 12), width=5, justify='center',
                                   bg=self.BG_CARD, fg=self.TEXT_PRIMARY, insertbackground=self.ACCENT, relief='flat', bd=0)
        self.count_entry.pack()
        self.count_entry.insert(0, "10")
        
        all_canvas = RoundedFrame(input_frame, radius=8, bg=self.BG_CARD, border_color=self.BORDER, border_width=1)
        all_canvas.pack(side='left', padx=8)
        all_canvas.configure(width=60, height=44, cursor="hand2")
        all_btn = tk.Label(all_canvas.inner_frame, text="all", font=('Segoe UI', 10), bg=self.BG_CARD, fg=self.TEXT_SECONDARY, cursor="hand2")
        all_btn.pack()
        all_btn.bind("<Button-1>", lambda e: self.set_all_questions())
        
        def all_hover(e, enter):
            bg = self.BTN_HOVER if enter else self.BG_CARD
            fg = self.TEXT_PRIMARY if enter else self.TEXT_SECONDARY
            all_canvas.bg_color = bg
            all_canvas._draw_rounded_rect()
            all_btn.configure(bg=bg, fg=fg)
            all_canvas.inner_frame.configure(bg=bg)
        
        all_canvas.bind("<Enter>", lambda e: all_hover(e, True))
        all_canvas.bind("<Leave>", lambda e: all_hover(e, False))
        all_btn.bind("<Enter>", lambda e: all_hover(e, True))
        all_btn.bind("<Leave>", lambda e: all_hover(e, False))
        
        start_canvas = RoundedFrame(container, radius=12, bg=self.SUCCESS)
        start_canvas.pack(pady=15)
        start_canvas.configure(width=200, height=52, cursor="hand2")
        start_label = tk.Label(start_canvas.inner_frame, text="Start Quiz", font=('Segoe UI', 12, 'bold'), bg=self.SUCCESS, fg="white", cursor="hand2")
        start_label.pack()
        
        def start_hover(e, enter):
            bg = self.SUCCESS_DARK if enter else self.SUCCESS
            start_canvas.bg_color = bg
            start_canvas._draw_rounded_rect()
            start_label.configure(bg=bg)
            start_canvas.inner_frame.configure(bg=bg)
        
        for w in [start_canvas, start_label]:
            w.bind("<Button-1>", lambda e: self.start_quiz())
            w.bind("<Enter>", lambda e: start_hover(e, True))
            w.bind("<Leave>", lambda e: start_hover(e, False))
        
        # Reset performance button
        reset_canvas = RoundedFrame(container, radius=8, bg=self.BG_CARD, border_color=self.BORDER, border_width=1)
        reset_canvas.pack(pady=(10, 0))
        reset_canvas.configure(width=200, height=38, cursor="hand2")
        reset_label = tk.Label(reset_canvas.inner_frame, text="🔄 Reset Performance Data", 
                              font=('Segoe UI', 9), bg=self.BG_CARD, fg=self.TEXT_MUTED, cursor="hand2")
        reset_label.pack()
        
        def reset_hover(e, enter):
            bg = self.BTN_HOVER if enter else self.BG_CARD
            fg = self.WARNING if enter else self.TEXT_MUTED
            border = self.WARNING if enter else self.BORDER
            reset_canvas.border_color = border
            reset_canvas.bg_color = bg
            reset_canvas._draw_rounded_rect()
            reset_canvas.inner_frame.configure(bg=bg)
            reset_label.configure(bg=bg, fg=fg)
        
        for w in [reset_canvas, reset_label]:
            w.bind("<Button-1>", lambda e: self.reset_performance_data())
            w.bind("<Enter>", lambda e: reset_hover(e, True))
            w.bind("<Leave>", lambda e: reset_hover(e, False))
    
    def set_all_questions(self):
        self.count_entry.delete(0, tk.END)
        self.count_entry.insert(0, "all")
    
    def create_mode_button(self, parent, text, mode, desc, side='left', padx=0):
        """Create a mode selection button"""
        btn_canvas = RoundedFrame(parent, radius=10, bg=self.BG_CARD, border_color=self.BORDER, border_width=2)
        btn_canvas.pack(side=side, padx=padx)
        btn_canvas.configure(width=175, height=70, cursor="hand2")
        
        inner = tk.Frame(btn_canvas.inner_frame, bg=self.BG_CARD)
        inner.pack(expand=True)
        
        title = tk.Label(inner, text=text, font=('Segoe UI', 11, 'bold'), 
                        bg=self.BG_CARD, fg=self.TEXT_SECONDARY, cursor="hand2")
        title.pack()
        
        subtitle = tk.Label(inner, text=desc, font=('Segoe UI', 9), 
                           bg=self.BG_CARD, fg=self.TEXT_MUTED, cursor="hand2")
        subtitle.pack(pady=(3, 0))
        
        # Store mode button references for highlighting
        if not hasattr(self, 'mode_buttons'):
            self.mode_buttons = {}
        self.mode_buttons[mode] = (btn_canvas, title, subtitle)
        
        def set_hover(enter):
            if self.game_mode == mode:
                return  # Don't change if selected
            bg = self.BTN_HOVER if enter else self.BG_CARD
            fg = self.TEXT_PRIMARY if enter else self.TEXT_SECONDARY
            border = self.TEXT_MUTED if enter else self.BORDER
            btn_canvas.border_color = border
            btn_canvas.bg_color = bg
            btn_canvas._draw_rounded_rect()
            btn_canvas.inner_frame.configure(bg=bg)
            inner.configure(bg=bg)
            title.configure(bg=bg, fg=fg)
            subtitle.configure(bg=bg)
        
        def select_mode():
            self.game_mode = mode
            self.update_mode_selection()
        
        for w in [btn_canvas, inner, title, subtitle]:
            w.bind("<Button-1>", lambda e: select_mode())
            w.bind("<Enter>", lambda e: set_hover(True))
            w.bind("<Leave>", lambda e: set_hover(False))
        
        # Highlight random mode by default
        if mode == 'random':
            self.root.after(100, self.update_mode_selection)
    
    def update_mode_selection(self):
        """Update visual state of mode buttons"""
        if not hasattr(self, 'mode_buttons'):
            return
        
        for mode, (canvas, title, subtitle) in self.mode_buttons.items():
            if mode == self.game_mode:
                # Selected state
                canvas.border_color = self.ACCENT
                canvas.bg_color = self.BG_HOVER
                canvas._draw_rounded_rect()
                canvas.inner_frame.configure(bg=self.BG_HOVER)
                title.master.configure(bg=self.BG_HOVER)
                title.configure(bg=self.BG_HOVER, fg=self.ACCENT)
                subtitle.configure(bg=self.BG_HOVER, fg=self.TEXT_SECONDARY)
            else:
                # Unselected state
                canvas.border_color = self.BORDER
                canvas.bg_color = self.BG_CARD
                canvas._draw_rounded_rect()
                canvas.inner_frame.configure(bg=self.BG_CARD)
                title.master.configure(bg=self.BG_CARD)
                title.configure(bg=self.BG_CARD, fg=self.TEXT_SECONDARY)
                subtitle.configure(bg=self.BG_CARD, fg=self.TEXT_MUTED)
    
    def start_quiz(self):
        user_input = self.count_entry.get().strip().lower()
        if user_input == "all":
            self.nr_of_questions = len(self.questions)
        else:
            try:
                self.nr_of_questions = min(int(user_input), len(self.questions))
                if self.nr_of_questions <= 0:
                    messagebox.showerror("Error", "Enter a valid number!")
                    return
            except ValueError:
                messagebox.showerror("Error", "Enter a number or 'all'!")
                return
        
        # Validate adaptive mode
        if self.game_mode == 'adaptive':
            # Get list of questions that have been answered before
            answered_questions = [i for i in range(len(self.questions)) 
                                 if self.performance_data.get(str(i), {}).get('timesAnswered', 0) > 0]
            
            if len(answered_questions) == 0:
                messagebox.showinfo("Review Mode", 
                    "No questions answered yet!\n\nPlay in Random Mode first to build your performance history.")
                return
            
            # Check if we have questions with errors
            questions_with_errors = sum(1 for i in answered_questions
                                       if self.performance_data.get(str(i), {}).get('timesIncorrect', 0) > 0)
            
            if questions_with_errors == 0:
                messagebox.showinfo("Review Mode", 
                    f"Great job! You haven't made any mistakes yet!\n\nYou have answered {len(answered_questions)} questions correctly.\n\nKeep practicing in Random Mode!")
                return
            
            # Use only answered questions in adaptive mode
            self.indexes_of_questions = answered_questions
            # Adjust number of questions if needed
            if self.nr_of_questions > len(answered_questions):
                self.nr_of_questions = len(answered_questions)
        else:
            # Random mode - use all questions
            self.indexes_of_questions = list(range(len(self.questions)))
        
        self.current_question_index = 0
        self.score = 0
        self.wrong_answers = []
        self.show_question()
    
    def select_adaptive_question(self):
        """Select question based on priority score (adaptive mode)"""
        # Calculate priority scores for available questions (only those answered before)
        priorities = []
        for idx in self.indexes_of_questions:
            # Only include questions that have been answered
            if self.performance_data.get(str(idx), {}).get('timesAnswered', 0) > 0:
                score = self.calculate_priority_score(idx)
                priorities.append((score, idx))
        
        # If no answered questions available, fallback to random
        if not priorities:
            return random.choice(self.indexes_of_questions)
        
        # Sort by priority score (descending)
        priorities.sort(reverse=True, key=lambda x: x[0])
        
        # Use weighted random selection favoring higher priority
        # Top 30% get much higher weight
        top_count = max(1, len(priorities) // 3)
        
        if priorities[0][0] > 0:  # If there are questions with errors
            # 70% chance to pick from top priority questions
            if random.random() < 0.7 and top_count > 0:
                return random.choice(priorities[:top_count])[1]
        
        # Otherwise pick from all available
        return random.choice(priorities)[1]
    
    def show_question(self):
        if self.current_question_index >= self.nr_of_questions:
            self.show_results()
            return
        
        self.clear_window()
        
        # Select question based on game mode
        if self.game_mode == 'adaptive':
            idx = self.select_adaptive_question()
        else:
            idx = random.choice(self.indexes_of_questions)
        
        self.indexes_of_questions.remove(idx)
        self.current_q = self.questions[idx]
        self.current_q_id = idx
        
        main_container = tk.Frame(self.root, bg=self.BG_DARK)
        main_container.pack(fill='both', expand=True)
        
        header = tk.Frame(main_container, bg=self.BG_CARD)
        header.pack(fill='x', side='top')
        header_inner = tk.Frame(header, bg=self.BG_CARD)
        header_inner.pack(fill='x', padx=30, pady=14)
        
        tk.Label(header_inner, text=f"{self.current_question_index + 1} / {self.nr_of_questions}", font=('Segoe UI', 12), bg=self.BG_CARD, fg=self.TEXT_MUTED).pack(side='left')
        tk.Label(header_inner, text=f"{self.score} correct", font=('Segoe UI', 12), bg=self.BG_CARD, fg=self.SUCCESS).pack(side='right')
        
        prog_bg = tk.Frame(header, bg=self.BG_DARK, height=3)
        prog_bg.pack(fill='x')
        progress = self.current_question_index / self.nr_of_questions
        prog_fill = tk.Frame(prog_bg, bg=self.ACCENT, height=3)
        prog_fill.place(relwidth=progress, relheight=1)
        
        content_container = tk.Frame(main_container, bg=self.BG_DARK)
        content_container.pack(fill='both', expand=True)
        content = tk.Frame(content_container, bg=self.BG_DARK)
        content.place(relx=0.5, rely=0.5, anchor='center', width=700)
        
        q_canvas = RoundedFrame(content, radius=12, bg=self.BG_CARD, border_color=self.BORDER, border_width=2)
        q_canvas.pack(fill='x', pady=(0, 20))
        q_canvas.configure(height=200)
        
        # Create scrollable text area for question
        q_frame = tk.Frame(q_canvas.inner_frame, bg=self.BG_CARD)
        q_frame.pack(fill='both', expand=True, padx=25, pady=20)
        
        # Text widget with scrollbar
        q_text = tk.Text(q_frame, font=('Consolas', 11), bg=self.BG_CARD, fg=self.TEXT_PRIMARY,
                        wrap='word', relief='flat', bd=0, highlightthickness=0,
                        padx=5, pady=5, height=8)
        
        scrollbar = ttk.Scrollbar(q_frame, orient='vertical', command=q_text.yview)
        q_text.configure(yscrollcommand=scrollbar.set)
        
        q_text.pack(side='left', fill='both', expand=True)
        scrollbar.pack(side='right', fill='y')
        
        # Insert question text
        q_text.insert('1.0', self.current_q['question'])
        q_text.config(state='disabled')
        
        # Reset selected answers for new question
        self.selected_answers = set()
        self.answer_buttons = {}
        
        # Check if this is a multi-answer question
        correct = self.current_q['correct']
        self.is_multi_answer = (self.current_q['answers'] and 
                                len(correct) > 1 and 
                                all(c.lower() in 'abcdefghij' for c in correct))
        
        if self.current_q['answers']:
            # Show hint for multi-answer questions
            if self.is_multi_answer:
                hint_label = tk.Label(content, text=f"Select {len(correct)} answers", 
                                     font=('Segoe UI', 10, 'italic'), bg=self.BG_DARK, fg=self.ACCENT)
                hint_label.pack(pady=(0, 10))
            
            for i, answer in enumerate(self.current_q['answers']):
                letter = chr(i + 97)
                self.create_answer_button(content, letter, answer)
            
            # Add submit button for multi-answer questions
            if self.is_multi_answer:
                self.create_submit_button(content)
        else:
            self.create_text_input(content)
    
    def create_answer_button(self, parent, letter, text):
        # Using simple frames
        btn_outer = tk.Frame(parent, bg=self.BORDER)
        btn_outer.pack(fill='x', pady=6)
        
        btn_frame = tk.Frame(btn_outer, bg=self.BG_CARD, cursor="hand2")
        btn_frame.pack(fill='x', padx=2, pady=2)
        
        inner = tk.Frame(btn_frame, bg=self.BG_CARD)
        inner.pack(fill='x', padx=20, pady=16)
        
        letter_lbl = tk.Label(inner, text=letter.upper(), font=('Segoe UI', 12, 'bold'), bg=self.BG_CARD, fg=self.TEXT_MUTED, width=2)
        letter_lbl.pack(side='left', anchor='n', pady=2)
        text_lbl = tk.Label(inner, text=text, font=('Segoe UI', 12), bg=self.BG_CARD, fg=self.TEXT_SECONDARY, 
                           anchor='w', wraplength=600, justify='left')
        text_lbl.pack(side='left', fill='x', expand=True, padx=15)
        
        # Store button references for multi-select UI updates
        self.answer_buttons[letter] = (btn_outer, btn_frame, inner, letter_lbl, text_lbl)
        
        def set_hover(enter):
            # Don't change appearance if selected in multi-answer mode
            if self.is_multi_answer and letter in self.selected_answers:
                return
            if enter:
                btn_outer.configure(bg=self.TEXT_MUTED)
                for w in [btn_frame, inner, letter_lbl, text_lbl]:
                    w.configure(bg=self.BTN_HOVER)
                letter_lbl.configure(fg=self.TEXT_PRIMARY)
                text_lbl.configure(fg=self.TEXT_PRIMARY)
            else:
                btn_outer.configure(bg=self.BORDER)
                for w in [btn_frame, inner, letter_lbl, text_lbl]:
                    w.configure(bg=self.BG_CARD)
                letter_lbl.configure(fg=self.TEXT_MUTED)
                text_lbl.configure(fg=self.TEXT_SECONDARY)
        
        def set_selected(selected):
            """Update button appearance for selected state"""
            if selected:
                btn_outer.configure(bg=self.ACCENT)
                for w in [btn_frame, inner, letter_lbl, text_lbl]:
                    w.configure(bg=self.BG_HOVER)
                letter_lbl.configure(fg=self.ACCENT)
                text_lbl.configure(fg=self.TEXT_PRIMARY)
            else:
                btn_outer.configure(bg=self.BORDER)
                for w in [btn_frame, inner, letter_lbl, text_lbl]:
                    w.configure(bg=self.BG_CARD)
                letter_lbl.configure(fg=self.TEXT_MUTED)
                text_lbl.configure(fg=self.TEXT_SECONDARY)
        
        def on_click(l):
            if self.is_multi_answer:
                # Toggle selection for multi-answer questions
                self.toggle_answer_selection(l)
            else:
                # Direct check for single-answer questions
                self.check_answer(l)
        
        # Only bind hover to outer frame to avoid child widget event issues
        btn_outer.bind("<Enter>", lambda e: set_hover(True))
        btn_outer.bind("<Leave>", lambda e: set_hover(False))
        
        # Bind click to all widgets
        for w in [btn_outer, btn_frame, inner, letter_lbl, text_lbl]:
            w.bind("<Button-1>", lambda e, l=letter: on_click(l))
    
    def toggle_answer_selection(self, letter):
        """Toggle selection of an answer for multi-answer questions"""
        if letter in self.selected_answers:
            self.selected_answers.remove(letter)
            selected = False
        else:
            self.selected_answers.add(letter)
            selected = True
        
        # Update button appearance
        if letter in self.answer_buttons:
            btn_outer, btn_frame, inner, letter_lbl, text_lbl = self.answer_buttons[letter]
            if selected:
                btn_outer.configure(bg=self.ACCENT)
                for w in [btn_frame, inner, letter_lbl, text_lbl]:
                    w.configure(bg=self.BG_HOVER)
                letter_lbl.configure(fg=self.ACCENT)
                text_lbl.configure(fg=self.TEXT_PRIMARY)
            else:
                btn_outer.configure(bg=self.BORDER)
                for w in [btn_frame, inner, letter_lbl, text_lbl]:
                    w.configure(bg=self.BG_CARD)
                letter_lbl.configure(fg=self.TEXT_MUTED)
                text_lbl.configure(fg=self.TEXT_SECONDARY)
    
    def create_submit_button(self, parent):
        """Create submit button for multi-answer questions"""
        submit_frame = tk.Frame(parent, bg=self.BG_DARK)
        submit_frame.pack(fill='x', pady=15)
        
        submit_canvas = RoundedFrame(submit_frame, radius=12, bg=self.SUCCESS)
        submit_canvas.pack()
        submit_canvas.configure(width=160, height=48, cursor="hand2")
        submit_lbl = tk.Label(submit_canvas.inner_frame, text="Submit Answers", 
                             font=('Segoe UI', 11, 'bold'), bg=self.SUCCESS, fg="white", cursor="hand2")
        submit_lbl.pack()
        
        def on_hover(e, enter):
            bg = self.SUCCESS_DARK if enter else self.SUCCESS
            submit_canvas.bg_color = bg
            submit_canvas._draw_rounded_rect()
            submit_canvas.inner_frame.configure(bg=bg)
            submit_lbl.configure(bg=bg)
        
        def on_submit():
            if not self.selected_answers:
                messagebox.showwarning("No Selection", "Please select at least one answer.")
                return
            # Join selected answers and check
            user_answer = ''.join(sorted(self.selected_answers))
            self.check_answer(user_answer)
        
        for w in [submit_canvas, submit_lbl]:
            w.bind("<Button-1>", lambda e: on_submit())
            w.bind("<Enter>", lambda e: on_hover(e, True))
            w.bind("<Leave>", lambda e: on_hover(e, False))
    
    def create_text_input(self, parent):
        input_frame = tk.Frame(parent, bg=self.BG_DARK)
        input_frame.pack(fill='x', pady=15)
        tk.Label(input_frame, text="Your answer", font=('Segoe UI', 10), bg=self.BG_DARK, fg=self.TEXT_MUTED).pack(anchor='w', pady=(0, 8))
        
        entry_canvas = RoundedFrame(input_frame, radius=10, bg=self.BG_CARD, border_color=self.BORDER, border_width=1)
        entry_canvas.pack(fill='x')
        entry_canvas.configure(height=44)
        self.answer_entry = tk.Entry(entry_canvas.inner_frame, font=('Segoe UI', 11), bg=self.BG_CARD, fg=self.TEXT_PRIMARY,
                                    insertbackground=self.ACCENT, width=50, relief='flat', bd=0)
        self.answer_entry.pack(ipady=5)
        self.answer_entry.focus()
        self.answer_entry.bind("<Return>", lambda e: self.check_answer(self.answer_entry.get()))
        
        submit_canvas = RoundedFrame(input_frame, radius=12, bg=self.BG_CARD, border_color=self.BORDER, border_width=1)
        submit_canvas.pack(pady=12)
        submit_canvas.configure(width=120, height=48, cursor="hand2")
        submit_lbl = tk.Label(submit_canvas.inner_frame, text="Submit", font=('Segoe UI', 10), bg=self.BG_CARD, fg=self.TEXT_SECONDARY, cursor="hand2")
        submit_lbl.pack()
        
        def on_hover(e, enter):
            bg = self.BTN_HOVER if enter else self.BG_CARD
            fg = self.TEXT_PRIMARY if enter else self.TEXT_SECONDARY
            border = self.TEXT_MUTED if enter else self.BORDER
            submit_canvas.border_color = border
            submit_canvas.bg_color = bg
            submit_canvas._draw_rounded_rect()
            submit_canvas.inner_frame.configure(bg=bg)
            submit_lbl.configure(bg=bg, fg=fg)
        
        for w in [submit_canvas, submit_lbl]:
            w.bind("<Button-1>", lambda e: self.check_answer(self.answer_entry.get()))
            w.bind("<Enter>", lambda e: on_hover(e, True))
            w.bind("<Leave>", lambda e: on_hover(e, False))
    
    def check_answer(self, user_answer):
        correct = self.current_q['correct']
        
        # Check if answer is correct (handle multiple correct answers)
        if self.current_q['answers'] and all(c.lower() in 'abcdefghij' for c in correct):
            # Multiple choice - compare sorted answers
            correct_sorted = ''.join(sorted(correct.lower()))
            user_sorted = ''.join(sorted(user_answer.lower()))
            is_correct = user_sorted == correct_sorted
        else:
            # Direct text answer - must match exactly
            is_correct = user_answer == correct
        
        # Update performance metrics
        self.update_performance(self.current_q_id, is_correct)
        
        if is_correct:
            self.score += 1
        else:
            self.wrong_answers.append((self.current_q, user_answer))
        self.current_question_index += 1
        self.show_feedback(is_correct, correct)
    
    def show_feedback(self, is_correct, correct_answer):
        self.clear_window()
        container = tk.Frame(self.root, bg=self.BG_DARK)
        container.place(relx=0.5, rely=0.5, anchor='center')
        
        color = self.SUCCESS if is_correct else self.ERROR
        icon = "✓" if is_correct else "✗"
        msg = "Correct!" if is_correct else "Incorrect"
        
        tk.Label(container, text=icon, font=('Segoe UI', 56), bg=self.BG_DARK, fg=color).pack(pady=(10, 12))
        tk.Label(container, text=msg, font=('Segoe UI', 24, 'bold'), bg=self.BG_DARK, fg=self.TEXT_PRIMARY).pack()
        
        if not is_correct:
            # Get the full text of the correct answer(s)
            if self.current_q['answers']:
                # Check if correct_answer contains multiple single letters (e.g., "ac")
                if all(c.lower() in 'abcdefghij' for c in correct_answer if c.strip()):
                    # Multiple choice answer(s)
                    correct_answers = []
                    for letter in correct_answer.lower():
                        if letter in 'abcdefghij':
                            correct_idx = ord(letter) - ord('a')
                            if correct_idx < len(self.current_q['answers']):
                                correct_text = self.current_q['answers'][correct_idx]
                                correct_answers.append(f"{letter.upper()}: {correct_text}")
                            else:
                                correct_answers.append(letter.upper())
                    
                    if len(correct_answers) > 1:
                        answer_display = "Multiple correct answers:\n" + "\n".join(correct_answers)
                    elif len(correct_answers) == 1:
                        answer_display = correct_answers[0]
                    else:
                        answer_display = correct_answer
                else:
                    # Direct text answer
                    answer_display = correct_answer
            else:
                answer_display = correct_answer
            
            ans_canvas = RoundedFrame(container, radius=12, bg=self.BG_CARD, border_color=self.BORDER, border_width=2)
            ans_canvas.pack(pady=22)
            ans_canvas.configure(width=600)
            
            ans_label = tk.Label(ans_canvas.inner_frame, text=f"Correct answer: {answer_display}", 
                                font=('Segoe UI', 12), bg=self.BG_CARD, fg=self.SUCCESS,
                                wraplength=550, justify='left', padx=20, pady=15)
            ans_label.pack()
        
        btn_canvas = RoundedFrame(container, radius=12, bg=self.BG_CARD, border_color=self.BORDER, border_width=2)
        btn_canvas.pack(pady=28)
        btn_canvas.configure(width=160, height=52, cursor="hand2")
        btn_lbl = tk.Label(btn_canvas.inner_frame, text="Continue", font=('Segoe UI', 11), bg=self.BG_CARD, fg=self.TEXT_SECONDARY, cursor="hand2")
        btn_lbl.pack()
        
        def on_hover(e, enter):
            bg = self.BTN_HOVER if enter else self.BG_CARD
            fg = self.TEXT_PRIMARY if enter else self.TEXT_SECONDARY
            border = self.TEXT_MUTED if enter else self.BORDER
            btn_canvas.border_color = border
            btn_canvas.bg_color = bg
            btn_canvas._draw_rounded_rect()
            btn_canvas.inner_frame.configure(bg=bg)
            btn_lbl.configure(bg=bg, fg=fg)
        
        for w in [btn_canvas, btn_lbl]:
            w.bind("<Button-1>", lambda e: self.show_question())
            w.bind("<Enter>", lambda e: on_hover(e, True))
            w.bind("<Leave>", lambda e: on_hover(e, False))
        
        if is_correct:
            self.pending_callback = self.root.after(1200, self.show_question)
    
    def show_results(self):
        self.clear_window()
        pct = (self.score / self.nr_of_questions) * 100
        container = tk.Frame(self.root, bg=self.BG_DARK)
        container.place(relx=0.5, rely=0.5, anchor='center')
        
        tk.Label(container, text="Quiz Complete!", font=('Segoe UI', 28, 'bold'), bg=self.BG_DARK, fg=self.TEXT_PRIMARY).pack(pady=(0, 30))
        
        color = self.SUCCESS if pct >= 70 else self.WARNING if pct >= 50 else self.ERROR
        card_canvas = RoundedFrame(container, radius=16, bg=self.BG_CARD, border_color=self.BORDER, border_width=2)
        card_canvas.pack(pady=10)
        card_canvas.configure(width=300, height=140)
        tk.Label(card_canvas.inner_frame, text=f"{pct:.0f}%", font=('Segoe UI', 48, 'bold'), bg=self.BG_CARD, fg=color).pack(pady=(10, 5))
        tk.Label(card_canvas.inner_frame, text=f"{self.score} of {self.nr_of_questions} correct", font=('Segoe UI', 13), bg=self.BG_CARD, fg=self.TEXT_SECONDARY).pack()
        
        btn_frame = tk.Frame(container, bg=self.BG_DARK)
        btn_frame.pack(pady=35)
        
        def create_btn(parent, text, command):
            btn_canvas = RoundedFrame(parent, radius=12, bg=self.BG_CARD, border_color=self.BORDER, border_width=2)
            btn_canvas.pack(side='left', padx=6)
            btn_canvas.configure(width=140, height=52, cursor="hand2")
            lbl = tk.Label(btn_canvas.inner_frame, text=text, font=('Segoe UI', 11), bg=self.BG_CARD, fg=self.TEXT_SECONDARY, cursor="hand2")
            lbl.pack()
            
            def on_hover(e, enter):
                bg = self.BTN_HOVER if enter else self.BG_CARD
                fg = self.TEXT_PRIMARY if enter else self.TEXT_SECONDARY
                border = self.TEXT_MUTED if enter else self.BORDER
                btn_canvas.border_color = border
                btn_canvas.bg_color = bg
                btn_canvas._draw_rounded_rect()
                btn_canvas.inner_frame.configure(bg=bg)
                lbl.configure(bg=bg, fg=fg)
            
            for w in [btn_canvas, lbl]:
                w.bind("<Button-1>", lambda e: command())
                w.bind("<Enter>", lambda e: on_hover(e, True))
                w.bind("<Leave>", lambda e: on_hover(e, False))
        
        if self.wrong_answers:
            create_btn(btn_frame, "Review Mistakes", self.review_mistakes)
        create_btn(btn_frame, "Play Again", self.show_welcome_screen)
        create_btn(btn_frame, "Exit", self.root.quit)
    
    def review_mistakes(self):
        self.clear_window()
        canvas = tk.Canvas(self.root, bg=self.BG_DARK, highlightthickness=0)
        scrollbar = ttk.Scrollbar(self.root, orient="vertical", command=canvas.yview)
        main = tk.Frame(canvas, bg=self.BG_DARK)
        main.bind("<Configure>", lambda e: canvas.configure(scrollregion=canvas.bbox("all")))
        window_id = canvas.create_window((0, 0), window=main, anchor="nw")
        canvas.configure(yscrollcommand=scrollbar.set)
        canvas.bind_all("<MouseWheel>", lambda e: canvas.yview_scroll(int(-1*(e.delta/120)), "units"))
        canvas.bind("<Configure>", lambda e: canvas.itemconfig(window_id, width=e.width))
        canvas.pack(side="left", fill="both", expand=True)
        scrollbar.pack(side="right", fill="y")
        
        content = tk.Frame(main, bg=self.BG_DARK)
        content.pack(fill='both', expand=True, padx=50, pady=30)
        
        tk.Label(content, text="Review Mistakes", font=('Segoe UI', 24, 'bold'), bg=self.BG_DARK, fg=self.TEXT_PRIMARY).pack(anchor='w', pady=(0, 8))
        tk.Label(content, text=f"{len(self.wrong_answers)} question{'s' if len(self.wrong_answers) != 1 else ''} answered incorrectly", 
                font=('Segoe UI', 11), bg=self.BG_DARK, fg=self.TEXT_MUTED).pack(anchor='w', pady=(0, 25))
        
        for i, (q, user_ans) in enumerate(self.wrong_answers, 1):
            # Card container
            card_outer = tk.Frame(content, bg=self.BORDER)
            card_outer.pack(fill='x', pady=10)
            
            card = tk.Frame(card_outer, bg=self.BG_CARD)
            card.pack(fill='x', padx=2, pady=2)
            
            card_inner = tk.Frame(card, bg=self.BG_CARD)
            card_inner.pack(fill='x', padx=25, pady=20)
            
            # Question number and text
            q_header = tk.Frame(card_inner, bg=self.BG_CARD)
            q_header.pack(fill='x', pady=(0, 15))
            
            tk.Label(q_header, text=f"Question {i}", font=('Segoe UI', 10, 'bold'), 
                    bg=self.BG_CARD, fg=self.ACCENT).pack(anchor='w')
            
            q_text_widget = tk.Text(q_header, font=('Segoe UI', 12), bg=self.BG_CARD, fg=self.TEXT_PRIMARY,
                                   wrap='word', height=2, relief='flat', bd=0, highlightthickness=0)
            q_text_widget.pack(fill='x', pady=(8, 0))
            q_text_widget.insert('1.0', q['question'])
            q_text_widget.config(state='disabled')
            
            # Answer section
            ans_frame = tk.Frame(card_inner, bg=self.BG_CARD)
            ans_frame.pack(fill='x')
            
            # Get the correct answer text (handle multiple correct answers)
            if q['answers']:
                correct_answers = q['correct']
                if len(correct_answers) > 1 and all(c.lower() in 'abcdefghij' for c in correct_answers):
                    # Multiple correct answers
                    correct_texts = []
                    for c in correct_answers.lower():
                        if c in 'abcdefghij':
                            idx = ord(c) - ord('a')
                            if idx < len(q['answers']):
                                correct_texts.append(f"{c.upper()}: {q['answers'][idx]}")
                    correct_text = "\n".join(correct_texts)
                else:
                    correct_idx = ord(q['correct']) - ord('a')
                    correct_text = q['answers'][correct_idx] if correct_idx < len(q['answers']) else q['correct']
            else:
                correct_text = q['correct']
            
            # Your answer row
            your_row = tk.Frame(ans_frame, bg=self.ERROR_DARK)
            your_row.pack(fill='x', pady=(0, 4))
            
            if q['answers']:
                # Handle multiple user answers
                if len(user_ans) > 1 and all(c.lower() in 'abcdefghij' for c in user_ans):
                    user_texts = []
                    for c in user_ans.lower():
                        if c in 'abcdefghij':
                            idx = ord(c) - ord('a')
                            if idx < len(q['answers']):
                                user_texts.append(f"{c.upper()}: {q['answers'][idx]}")
                    user_text = "\n".join(user_texts) if user_texts else user_ans
                else:
                    user_idx = ord(user_ans) - ord('a')
                    user_text = q['answers'][user_idx] if user_idx < len(q['answers']) else user_ans
            else:
                user_text = user_ans
            
            tk.Label(your_row, text=f"  ✗  Your answer:  {user_text}", font=('Segoe UI', 11), 
                    bg=self.ERROR_DARK, fg="white", padx=15, pady=10, anchor='w', 
                    wraplength=600, justify='left').pack(fill='x')
            
            # Correct answer row
            correct_row = tk.Frame(ans_frame, bg=self.SUCCESS_DARK)
            correct_row.pack(fill='x')
            
            tk.Label(correct_row, text=f"  ✓  Correct answer:  {correct_text}", font=('Segoe UI', 11), 
                    bg=self.SUCCESS_DARK, fg="white", padx=15, pady=10, anchor='w', 
                    wraplength=600, justify='left').pack(fill='x')
        
        # Back button
        btn_frame = tk.Frame(content, bg=self.BG_DARK)
        btn_frame.pack(pady=25)
        
        btn_outer = tk.Frame(btn_frame, bg=self.BORDER)
        btn_outer.pack()
        
        btn = tk.Frame(btn_outer, bg=self.BG_CARD, cursor="hand2")
        btn.pack(padx=2, pady=2)
        
        back_lbl = tk.Label(btn, text="Back to Results", font=('Segoe UI', 11), 
                           bg=self.BG_CARD, fg=self.TEXT_SECONDARY, padx=30, pady=12, cursor="hand2")
        back_lbl.pack()
        
        def on_hover(e, enter):
            bg = self.BTN_HOVER if enter else self.BG_CARD
            fg = self.TEXT_PRIMARY if enter else self.TEXT_SECONDARY
            border = self.TEXT_MUTED if enter else self.BORDER
            btn_outer.configure(bg=border)
            btn.configure(bg=bg)
            back_lbl.configure(bg=bg, fg=fg)
        
        for w in [btn_outer, btn, back_lbl]:
            w.bind("<Button-1>", lambda e: self.show_results())
            w.bind("<Enter>", lambda e: on_hover(e, True))
            w.bind("<Leave>", lambda e: on_hover(e, False))


def main():
    root = tk.Tk()
    app = QuizApp(root)
    root.mainloop()


if __name__ == "__main__":
    main()