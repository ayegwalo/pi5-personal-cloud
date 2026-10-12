# Raspberry Pi 5 Personal Cloud Storage & Telemetry Configuration

This repository contains the complete configuration blueprint to transform a **Raspberry Pi 5** into a secure, energy-efficient, private cloud storage server. The setup maps a **1TB external hard drive**, broadcasts it locally to macOS and iOS via **Samba**, secures global remote access using **Tailscale**, and configures automated hard drive spin-down parameters to optimize power consumption.

---

## ⚡ Setup Power Profiles & Electrical Cost Estimation

Because the Raspberry Pi 5 features an advanced on-board Power Management IC (PMIC), we can track exact motherboard metrics alongside the drive adapter configurations (`12V ⎓ 1.5A`). Below is the data showing real-world power draw:

| Operating State | Raspberry Pi 5 | 1TB External HDD (Wall-Powered) | Combined Total Wattage | Estimated Monthly Cost (Austria Average) |
| :--- | :--- | :--- | :--- | :--- |
| **Idle / Sleep Mode** | ~3.33 Watts | ~2.00 Watts | **~5.33 Watts** | **~€0.80 – €1.20** |
| **Active Read/Write** | ~5.00 Watts | ~7.00 Watts | **~12.00 Watts** | **~€1.80 – €2.50** |

*Note: By implementing Phase 4, the disk motor turns off during idle periods, dropping your continuous setup footprint down to the minimal ~5.3W baseline.*

---

## 🚀 Automated All-In-One Deployment Script

To deploy this entire infrastructure automatically without running commands one by one, save the source below into a file named `setup_cloud.sh`, make it executable, and run it. The script automatically isolates your drive partition's hardware UUID and builds the target architecture across all 5 phases:

```bash
#!/bin/bash
# automated_cloud_installer.sh

# 1. Dynamically discover the hardware partition token
DRIVE_UUID=$(sudo blkid -o value -s UUID /dev/sda1)

if [ -z "$DRIVE_UUID" ]; then
    echo "❌ ERROR: 1TB Hard Drive (/dev/sda1) not detected on blue USB ports!"
    exit 1
fi

echo "✅ Target 1TB Storage Identified with UUID: $DRIVE_UUID"
echo "⚙️  Beginning fully integrated Phase 1 to 5 deployment..."
sleep 2

# [PHASE 1] Mount Point & System Partition Formatting
sudo mkdir -p /media/remotedrive
echo "UUID=$DRIVE_UUID /media/remotedrive auto defaults,nofail,user,rw 0 0" | sudo tee -a /etc/fstab
sudo mount -a
sudo chown -R $USER:$USER /media/remotedrive

# [PHASE 2] Tailscale Cryptographic Mesh Orchestration
curl -fsSL https://tailscale.com | sh
sudo tailscale up --accept-dns=true

# [PHASE 3] Samba Remote Directory Mapping Profiles
sudo apt update && sudo apt install samba samba-common-bin -y
echo -e "\n[ExternalDrive]\npath = /media/remotedrive\nbrowseable = yes\nread only = no\nguest ok = no\ncreate mask = 0775\ndirectory mask = 0775" | sudo tee -a /etc/samba/smb.conf
sudo systemctl restart smbd

# [PHASE 4] Re-engineering Drive Idle Low-Power Standby States
sudo apt install hdparm -y
echo -e "\n/dev/sda {\n    spindown_time = 120\n}" | sudo tee -a /etc/hdparm.conf
sudo hdparm -K 1 /dev/sda
sudo hdparm -S 120 /dev/sda

# [PHASE 5] Diagnostics Commit
echo "=========================================================="
echo "🎉 DEPLOYMENT FINISHED ACTIVE: CLOUD ECOSYSTEM IS ONLINE!"
echo "=========================================================="
sudo hdparm -C /dev/sda
```

---

## 🛠️ Step-by-Step Manual Deployment Guide

If you prefer to configure your environment phase by phase, use the specific operational command layout blocks detailed below:

### Phase 1: Storage Provisioning & Permanent Mounting
```bash
# 1. View connected block storage devices to verify hardware locations
lsblk

# 2. Extract the unique file system hardware token (UUID) of your 1TB partition
sudo blkid /dev/sda1

# 3. Open the permanent system mount layout tables
sudo nano /etc/fstab

# --- APPEND THIS LINE TO THE ABSOLUTE BOTTOM OF /etc/fstab ---
UUID=YOUR-UUID-HERE /media/remotedrive auto defaults,nofail,user,rw 0 0
# -------------------------------------------------------------

# 4. Enforce system mounting rules immediately to attach the partition
sudo mount -a

# 5. Overhaul directory permissions so your standard user account has write access
sudo chown -R $USER:$USER /media/remotedrive
```

### Phase 2: Secure Mesh Network Orchestration (Tailscale)
```bash
# 1. Download and install the core Tailscale software client engine
curl -fsSL https://tailscale.com | sh

# 2. Ignite the software stack and generate your private global node authentication link
sudo tailscale up
```

### Phase 3: Multi-Platform Network File Sharing (Samba)
```bash
# 1. Update system package indexing files and deploy the core Samba framework
sudo apt update && sudo apt install samba samba-common-bin -y

# 2. Open the Samba service infrastructure configuration file
sudo nano /etc/samba/smb.conf

# --- APPEND THIS SHARE CONFIGURATION BLOCK TO THE ABSOLUTE BOTTOM OF /etc/samba/smb.conf ---
[ExternalDrive]
path = /media/remotedrive
browseable = yes
read only = no
guest ok = no
create mask = 0775
directory mask = 0775
# -----------------------------------------------------------------------------------------

# 3. Restart the background networking daemons to push the newly defined paths live
sudo systemctl restart smbd
```

### Phase 4: Energy Efficiency & Hardware Idle Control
```bash
# 1. Deploy the hardware-level disk register management tool
sudo apt install hdparm -y

# 2. Open the persistent hdparm configuration profile
sudo nano /etc/hdparm.conf

# --- APPEND THIS AUTOMATION BLOCK TO THE ABSOLUTE BOTTOM OF /etc/hdparm.conf ---
/dev/sda {
    spindown_time = 120
}
# -------------------------------------------------------------------------------

# 3. Force the 10-minute hardware-level idle sleep timeout parameters directly to the disk
sudo hdparm -K 1 /dev/sda
sudo hdparm -S 120 /dev/sda
```

### Phase 5: Monitoring, Diagnostics & Live Telemetry
```bash
# 1. Query the live hardware mechanical spindle state of the disk partition without waking it up
sudo hdparm -C /dev/sda

# 2. Interrogate the Raspberry Pi 5 PMIC bus to read real-time voltage rails and telemetry
vcgencmd pmic_read_adc
```

---

## 📡 Remote Mapping Blueprint

### macOS (Finder Client)
1. Launch **Finder**, choose **Go** from the top menu, and select **Connect to Server...** (or press `Cmd + K`).
2. Supply the unified path utilizing your specific Tailscale URL prefix:
   ```text
   smb://your-node-name.your-tailnet-id.ts.net/ExternalDrive
   ```
3. Mark the connection type as **Registered User** and authorize using your Raspberry Pi system username and password credentials.

### iOS / iPadOS (Native Files App)
1. Turn on the **Tailscale app** connection tunnel on your mobile device.
2. Launch the Apple **Files** app, navigate to the **Browse** shelf tab, tap the **More (...)** icon, and pick **Connect to Server**.
3. Supply your raw Tailscale domain node identifier: `your-node-name.your-tailnet-id.ts.net`.
4. Pick **Registered User** and input your authentication details to access your storage space cleanly from any destination globally.

