import sqlite3

def criar_banco():
    conn = sqlite3.connect("tags.db")
    cursor = conn.cursor()

    cursor.execute("""
        CREATE TABLE IF NOT EXISTS tags_autorizadas (
            uid TEXT PRIMARY KEY,
            nome TEXT NOT NULL
        )
    """)

    conn.commit()
    conn.close()
    print("[INFO] Banco de dados e tabela criados com sucesso!")

if __name__ == "__main__":
    criar_banco()
