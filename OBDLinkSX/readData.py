import obd

connection = obd.OBD()
cmd = obd.commands.SPEED
response = connection.query(cmd)
print response.value
print response.value.to("mph")