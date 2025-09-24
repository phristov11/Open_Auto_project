setup_autostart.sh
#!/bin/bash
# Setup Dash autostart as a systemd service
# This will run /home/pi/Desktop/start.sh at boot

SERVICE_NAME="dash.service"
WORKING_DIR="/home/pi/Desktop"
SERVICE_PATH="/etc/systemd/system/${SERVICE_NAME}"

echo "==> Setting up ${SERVICE_NAME} for autostart..."

# Stop and remove old service if it exists
if [ -f "$SERVICE_PATH" ]; then
  echo "Stopping and removing previous service..."
  sudo systemctl stop $SERVICE_NAME || true
  sudo systemctl disable $SERVICE_NAME || true
  sudo systemctl unmask $SERVICE_NAME || true
  sudo rm -f $SERVICE_PATH
fi

# Create new service file
echo "Creating new service file at $SERVICE_PATH..."
sudo bash -c "cat > $SERVICE_PATH <<EOF
[Unit]
Description=Dash with Rotary Encoder + ALSA
After=graphical.target sound.target

[Service]
Type=simple
User=pi
Group=audio
WorkingDirectory=${WORKING_DIR}
ExecStart=${WORKING_DIR}/start.sh
Restart=on-failure
RestartSec=5
KillMode=process
TimeoutSec=infinity
Environment=DISPLAY=:0
Environment=XAUTHORITY=/home/pi/.Xauthority
StandardOutput=journal
StandardError=journal

[Install]
WantedBy=graphical.target
EOF"

# Reload systemd and enable/start service
echo "Reloading systemd..."
sudo systemctl daemon-reload

echo "Enabling ${SERVICE_NAME} to run at boot..."
sudo systemctl enable $SERVICE_NAME

echo "Starting ${SERVICE_NAME} now..."
sudo systemctl start $SERVICE_NAME

echo "✅ Setup complete!"
echo "Check logs anytime with: journalctl -u ${SERVICE_NAME} -f"

⚡ Usage

Save as setup_autostart.sh on your Pi:

nano ~/setup_autostart.sh


(paste the script, save, exit).

Make it executable:

chmod +x ~/setup_autostart.sh


Run it once:

./setup_autostart.sh


From then on, /home/pi/Desktop/start.sh will always launch at boot. 🚀
