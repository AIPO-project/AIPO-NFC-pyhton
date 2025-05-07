import sqlite3

def cadastrar_tag(uid, nome):
    conn = sqlite3.connect("tags.db")
    cursor = conn.cursor()
    try:
        cursor.execute("INSERT INTO tags_autorizadas (uid, nome) VALUES (?, ?)", (uid, nome))
        conn.commit()
        print(f"[SUCESSO] TAG {uid} cadastrada para {nome}")
    except sqlite3.IntegrityError:
        print(f"[AVISO] TAG {uid} já está cadastrada.")
    conn.close()

uid = input("Digite o UID da TAG que deseja cadastrar: ").strip()
nome = input("Digite o nome do proprietário da TAG: ").strip()

cadastrar_tag(uid, nome)
