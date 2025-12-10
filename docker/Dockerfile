FROM python:3.11-slim
WORKDIR /app
RUN pip install pyserial matplotlib
COPY telemetry/ telemetry/
CMD ["python3", "telemetry/telemetry.py", "--port", "/dev/ttyUSB0", "--baud", "115200"]
