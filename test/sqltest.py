
# create a test sqlite3 databse file sqltest.bd
import sqlite3
import string
import random


dbfilename = r"sqltest.db"
tablename_mailing = r"mailing"
tablename_mailcount = r"mailcount"

mocktest_table_domains = "domains" # prepare 200,000 domains

def prepare_db():

    conn = sqlite3.connect(dbfilename)
    c = conn.cursor()

    sql = 'create table if not exists ' + tablename_mailing + ' (addr VARCHAR(255) not null , date DATE)'
    c.execute(sql)

    sql = 'create table if not exists ' + tablename_mailcount + ' (domain VARCHAR(255) not null, count INTEGER, date DATE)'
    c.execute(sql)


    sql = 'create table if not exists ' + mocktest_table_domains + ' (domain VARCHAR(255))'
    conn.commit()

    c.close()
    conn.close()
    
def random_string_generator(size=20, chars=string.ascii_lowercase + string.digits):
    return ''.join(random.choice(chars) for x in range(size))

def create_random_email():
    name = random_string_generator( 10   )
    domain = random_string_generator( 15 )
    return name+ r"@" + domain + r".com"

def mocktest_fill_table_domains():
    random_string_generator(size=15, chars=string.ascii_lowercase + string.digits):

#print  create_random_email()
prepare_db()


